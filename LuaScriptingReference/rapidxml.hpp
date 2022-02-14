#ifndef RAPIDXML_HPP_INCLUDED
#define RAPIDXML_HPP_INCLUDED     
#if !defined(RAPIDXML_NO_STDLIB)
    #include <cstdlib> 
    #include <cassert> 
    #include <new> 
#endif  
#ifdef _MSC_VER
    #pragma warning(push)
    #pragma warning(disable:4127) 
#endif  
    
#if defined(RAPIDXML_NO_EXCEPTIONS)

#define RAPIDXML_PARSE_ERROR(what, where) { parse_error_handler(what, where); assert(0); }

namespace rapidxml
{                
    void parse_error_handler(const char *what, void *where);
}

#else
    
#include <exception> 

#define RAPIDXML_PARSE_ERROR(what, where) throw parse_error(what, where)

namespace rapidxml
{           
    class parse_error: public std::exception
    {
    
    public: 
        parse_error(const char *what, void *where)
            : m_what(what)
            , m_where(where)
        {
        }  
        virtual const char *what() const throw()
        {
            return m_what;
        }   
        template<class Ch>
        Ch *where() const
        {
            return reinterpret_cast<Ch *>(m_where);
        }

    private:  

        const char *m_what;
        void *m_where;

    };
}

#endif  

#ifndef RAPIDXML_STATIC_POOL_SIZE   
    #define RAPIDXML_STATIC_POOL_SIZE (64 * 1024)
#endif

#ifndef RAPIDXML_DYNAMIC_POOL_SIZE   
    #define RAPIDXML_DYNAMIC_POOL_SIZE (64 * 1024)
#endif

#ifndef RAPIDXML_ALIGNMENT    
    #define RAPIDXML_ALIGNMENT sizeof(void *)
#endif

namespace rapidxml
{ 
    template<class Ch> class xml_node;
    template<class Ch> class xml_attribute;
    template<class Ch> class xml_document;  
    enum node_type
    {
        node_document, 
        node_element, 
        node_data, 
        node_cdata, 
        node_comment, 
        node_declaration, 
        node_doctype, 
        node_pi 
    };       
    const int parse_no_data_nodes = 0x1;       
    const int parse_no_element_values = 0x2;     
    const int parse_no_string_terminators = 0x4;     
    const int parse_no_entity_translation = 0x8;     
    const int parse_no_utf8 = 0x10;     
    const int parse_declaration_node = 0x20;     
    const int parse_comment_nodes = 0x40;      
    const int parse_doctype_node = 0x80;     
    const int parse_pi_nodes = 0x100;      
    const int parse_validate_closing_tags = 0x200;      
    const int parse_trim_whitespace = 0x400;       
    const int parse_normalize_whitespace = 0x800;         
    const int parse_default = 0;        
    const int parse_non_destructive = parse_no_string_terminators | parse_no_entity_translation;   
    const int parse_fastest = parse_non_destructive | parse_no_data_nodes;    
    const int parse_full = parse_declaration_node | parse_comment_nodes | parse_doctype_node | parse_pi_nodes | parse_validate_closing_tags;   
    namespace internal
    {  
        template<int Dummy>
        struct lookup_tables
        {
            static const unsigned char lookup_whitespace[256]; 
            static const unsigned char lookup_node_name[256]; 
            static const unsigned char lookup_text[256]; 
            static const unsigned char lookup_text_pure_no_ws[256]; 
            static const unsigned char lookup_text_pure_with_ws[256]; 
            static const unsigned char lookup_attribute_name[256]; 
            static const unsigned char lookup_attribute_data_1[256]; 
            static const unsigned char lookup_attribute_data_1_pure[256]; 
            static const unsigned char lookup_attribute_data_2[256]; 
            static const unsigned char lookup_attribute_data_2_pure[256]; 
            static const unsigned char lookup_digits[256]; 
            static const unsigned char lookup_upcase[256]; 
        }; 
        template<class Ch>
        inline std::size_t measure(const Ch *p)
        {
            const Ch *tmp = p;
            while (*tmp) 
                ++tmp;
            return tmp - p;
        } 
        template<class Ch>
        inline bool compare(const Ch *p1, std::size_t size1, const Ch *p2, std::size_t size2, bool case_sensitive)
        {
            if (size1 != size2)
                return false;
            if (case_sensitive)
            {
                for (const Ch *end = p1 + size1; p1 < end; ++p1, ++p2)
                    if (*p1 != *p2)
                        return false;
            }
            else
            {
                for (const Ch *end = p1 + size1; p1 < end; ++p1, ++p2)
                    if (lookup_tables<0>::lookup_upcase[static_cast<unsigned char>(*p1)] != lookup_tables<0>::lookup_upcase[static_cast<unsigned char>(*p2)])
                        return false;
            }
            return true;
        }
    }                                     
    template<class Ch = char>
    class memory_pool
    {
        
    public: 
        typedef void *(alloc_func)(std::size_t); 
        typedef void (free_func)(void *);   
        memory_pool()
            : m_alloc_func(0)
            , m_free_func(0)
        {
            init();
        }   
        ~memory_pool()
        {
            clear();
        }          
        xml_node<Ch> *allocate_node(node_type type, 
                                    const Ch *name = 0, const Ch *value = 0, 
                                    std::size_t name_size = 0, std::size_t value_size = 0)
        {
            void *memory = allocate_aligned(sizeof(xml_node<Ch>));
            xml_node<Ch> *node = new(memory) xml_node<Ch>(type);
            if (name)
            {
                if (name_size > 0)
                    node->name(name, name_size);
                else
                    node->name(name);
            }
            if (value)
            {
                if (value_size > 0)
                    node->value(value, value_size);
                else
                    node->value(value);
            }
            return node;
        }         
        xml_attribute<Ch> *allocate_attribute(const Ch *name = 0, const Ch *value = 0, 
                                              std::size_t name_size = 0, std::size_t value_size = 0)
        {
            void *memory = allocate_aligned(sizeof(xml_attribute<Ch>));
            xml_attribute<Ch> *attribute = new(memory) xml_attribute<Ch>;
            if (name)
            {
                if (name_size > 0)
                    attribute->name(name, name_size);
                else
                    attribute->name(name);
            }
            if (value)
            {
                if (value_size > 0)
                    attribute->value(value, value_size);
                else
                    attribute->value(value);
            }
            return attribute;
        }       
        Ch *allocate_string(const Ch *source = 0, std::size_t size = 0)
        {
            assert(source || size); 
            if (size == 0)
                size = internal::measure(source) + 1;
            Ch *result = static_cast<Ch *>(allocate_aligned(size * sizeof(Ch)));
            if (source)
                for (std::size_t i = 0; i < size; ++i)
                    result[i] = source[i];
            return result;
        }         
        xml_node<Ch> *clone_node(const xml_node<Ch> *source, xml_node<Ch> *result = 0)
        { 
            if (result)
            {
                result->remove_all_attributes();
                result->remove_all_nodes();
                result->type(source->type());
            }
            else
                result = allocate_node(source->type()); 
            result->name(source->name(), source->name_size());
            result->value(source->value(), source->value_size()); 
            for (xml_node<Ch> *child = source->first_node(); child; child = child->next_sibling())
                result->append_node(clone_node(child));
            for (xml_attribute<Ch> *attr = source->first_attribute(); attr; attr = attr->next_attribute())
                result->append_attribute(allocate_attribute(attr->name(), attr->value(), attr->name_size(), attr->value_size()));

            return result;
        }   
        void clear()
        {
            while (m_begin != m_static_memory)
            {
                char *previous_begin = reinterpret_cast<header *>(align(m_begin))->previous_begin;
                if (m_free_func)
                    m_free_func(m_begin);
                else
                    delete[] m_begin;
                m_begin = previous_begin;
            }
            init();
        }             
        void set_allocator(alloc_func *af, free_func *ff)
        {
            assert(m_begin == m_static_memory && m_ptr == align(m_begin)); 
            m_alloc_func = af;
            m_free_func = ff;
        }

    private:

        struct header
        {
            char *previous_begin;
        };

        void init()
        {
            m_begin = m_static_memory;
            m_ptr = align(m_begin);
            m_end = m_static_memory + sizeof(m_static_memory);
        }
        
        char *align(char *ptr)
        {
            std::size_t alignment = ((RAPIDXML_ALIGNMENT - (std::size_t(ptr) & (RAPIDXML_ALIGNMENT - 1))) & (RAPIDXML_ALIGNMENT - 1));
            return ptr + alignment;
        }
        
        char *allocate_raw(std::size_t size)
        { 
            void *memory;   
            if (m_alloc_func) 
            {
                memory = m_alloc_func(size);
                assert(memory); 
            }
            else
            {
                memory = new char[size];
#ifdef RAPIDXML_NO_EXCEPTIONS
                if (!memory) 
                    RAPIDXML_PARSE_ERROR("out of memory", 0);
#endif
            }
            return static_cast<char *>(memory);
        }
        
        void *allocate_aligned(std::size_t size)
        { 
            char *result = align(m_ptr); 
            if (result + size > m_end)
            { 
                std::size_t pool_size = RAPIDXML_DYNAMIC_POOL_SIZE;
                if (pool_size < size)
                    pool_size = size; 
                std::size_t alloc_size = sizeof(header) + (2 * RAPIDXML_ALIGNMENT - 2) + pool_size; 
                char *raw_memory = allocate_raw(alloc_size); 
                char *pool = align(raw_memory);
                header *new_header = reinterpret_cast<header *>(pool);
                new_header->previous_begin = m_begin;
                m_begin = raw_memory;
                m_ptr = pool + sizeof(header);
                m_end = raw_memory + alloc_size; 
                result = align(m_ptr);
            } 
            m_ptr = result + size;
            return result;
        }

        char *m_begin; 
        char *m_ptr; 
        char *m_end; 
        char m_static_memory[RAPIDXML_STATIC_POOL_SIZE]; 
        alloc_func *m_alloc_func; 
        free_func *m_free_func; 
    };     
    template<class Ch = char>
    class xml_base
    {

    public:   
        xml_base()
            : m_name(0)
            , m_value(0)
            , m_parent(0)
        {
        }        
        Ch *name() const
        {
            return m_name ? m_name : nullstr();
        }   
        std::size_t name_size() const
        {
            return m_name ? m_name_size : 0;
        }      
        Ch *value() const
        {
            return m_value ? m_value : nullstr();
        }   
        std::size_t value_size() const
        {
            return m_value ? m_value_size : 0;
        }               
        void name(const Ch *name, std::size_t size)
        {
            m_name = const_cast<Ch *>(name);
            m_name_size = size;
        }   
        void name(const Ch *name)
        {
            this->name(name, internal::measure(name));
        }                
        void value(const Ch *value, std::size_t size)
        {
            m_value = const_cast<Ch *>(value);
            m_value_size = size;
        }   
        void value(const Ch *value)
        {
            this->value(value, internal::measure(value));
        }    
        xml_node<Ch> *parent() const
        {
            return m_parent;
        }

    protected: 
        static Ch *nullstr()
        {
            static Ch zero = Ch('\0');
            return &zero;
        }

        Ch *m_name; 
        Ch *m_value; 
        std::size_t m_name_size; 
        std::size_t m_value_size; 
        xml_node<Ch> *m_parent; 

    };     
    template<class Ch = char>
    class xml_attribute: public xml_base<Ch>
    {

        friend class xml_node<Ch>;
    
    public:    
        xml_attribute()
        {
        }    
        xml_document<Ch> *document() const
        {
            if (xml_node<Ch> *node = this->parent())
            {
                while (node->parent())
                    node = node->parent();
                return node->type() == node_document ? static_cast<xml_document<Ch> *>(node) : 0;
            }
            else
                return 0;
        }     
        xml_attribute<Ch> *previous_attribute(const Ch *name = 0, std::size_t name_size = 0, bool case_sensitive = true) const
        {
            if (name)
            {
                if (name_size == 0)
                    name_size = internal::measure(name);
                for (xml_attribute<Ch> *attribute = m_prev_attribute; attribute; attribute = attribute->m_prev_attribute)
                    if (internal::compare(attribute->name(), attribute->name_size(), name, name_size, case_sensitive))
                        return attribute;
                return 0;
            }
            else
                return this->m_parent ? m_prev_attribute : 0;
        }     
        xml_attribute<Ch> *next_attribute(const Ch *name = 0, std::size_t name_size = 0, bool case_sensitive = true) const
        {
            if (name)
            {
                if (name_size == 0)
                    name_size = internal::measure(name);
                for (xml_attribute<Ch> *attribute = m_next_attribute; attribute; attribute = attribute->m_next_attribute)
                    if (internal::compare(attribute->name(), attribute->name_size(), name, name_size, case_sensitive))
                        return attribute;
                return 0;
            }
            else
                return this->m_parent ? m_next_attribute : 0;
        }

    private:

        xml_attribute<Ch> *m_prev_attribute; 
        xml_attribute<Ch> *m_next_attribute; 
    
    };          
    template<class Ch = char>
    class xml_node: public xml_base<Ch>
    {

    public:     
        xml_node(node_type type)
            : m_type(type)
            , m_first_node(0)
            , m_first_attribute(0)
        {
        }    
        node_type type() const
        {
            return m_type;
        }    
        xml_document<Ch> *document() const
        {
            xml_node<Ch> *node = const_cast<xml_node<Ch> *>(this);
            while (node->parent())
                node = node->parent();
            return node->type() == node_document ? static_cast<xml_document<Ch> *>(node) : 0;
        }     
        xml_node<Ch> *first_node(const Ch *name = 0, std::size_t name_size = 0, bool case_sensitive = true) const
        {
            if (name)
            {
                if (name_size == 0)
                    name_size = internal::measure(name);
                for (xml_node<Ch> *child = m_first_node; child; child = child->next_sibling())
                    if (internal::compare(child->name(), child->name_size(), name, name_size, case_sensitive))
                        return child;
                return 0;
            }
            else
                return m_first_node;
        }       
        xml_node<Ch> *last_node(const Ch *name = 0, std::size_t name_size = 0, bool case_sensitive = true) const
        {
            assert(m_first_node); 
            if (name)
            {
                if (name_size == 0)
                    name_size = internal::measure(name);
                for (xml_node<Ch> *child = m_last_node; child; child = child->previous_sibling())
                    if (internal::compare(child->name(), child->name_size(), name, name_size, case_sensitive))
                        return child;
                return 0;
            }
            else
                return m_last_node;
        }       
        xml_node<Ch> *previous_sibling(const Ch *name = 0, std::size_t name_size = 0, bool case_sensitive = true) const
        {
            assert(this->m_parent); 
            if (name)
            {
                if (name_size == 0)
                    name_size = internal::measure(name);
                for (xml_node<Ch> *sibling = m_prev_sibling; sibling; sibling = sibling->m_prev_sibling)
                    if (internal::compare(sibling->name(), sibling->name_size(), name, name_size, case_sensitive))
                        return sibling;
                return 0;
            }
            else
                return m_prev_sibling;
        }       
        xml_node<Ch> *next_sibling(const Ch *name = 0, std::size_t name_size = 0, bool case_sensitive = true) const
        {
            assert(this->m_parent); 
            if (name)
            {
                if (name_size == 0)
                    name_size = internal::measure(name);
                for (xml_node<Ch> *sibling = m_next_sibling; sibling; sibling = sibling->m_next_sibling)
                    if (internal::compare(sibling->name(), sibling->name_size(), name, name_size, case_sensitive))
                        return sibling;
                return 0;
            }
            else
                return m_next_sibling;
        }     
        xml_attribute<Ch> *first_attribute(const Ch *name = 0, std::size_t name_size = 0, bool case_sensitive = true) const
        {
            if (name)
            {
                if (name_size == 0)
                    name_size = internal::measure(name);
                for (xml_attribute<Ch> *attribute = m_first_attribute; attribute; attribute = attribute->m_next_attribute)
                    if (internal::compare(attribute->name(), attribute->name_size(), name, name_size, case_sensitive))
                        return attribute;
                return 0;
            }
            else
                return m_first_attribute;
        }     
        xml_attribute<Ch> *last_attribute(const Ch *name = 0, std::size_t name_size = 0, bool case_sensitive = true) const
        {
            if (name)
            {
                if (name_size == 0)
                    name_size = internal::measure(name);
                for (xml_attribute<Ch> *attribute = m_last_attribute; attribute; attribute = attribute->m_prev_attribute)
                    if (internal::compare(attribute->name(), attribute->name_size(), name, name_size, case_sensitive))
                        return attribute;
                return 0;
            }
            else
                return m_first_attribute ? m_last_attribute : 0;
        }    
        void type(node_type type)
        {
            m_type = type;
        }     
        void prepend_node(xml_node<Ch> *child)
        {
            assert(child && !child->parent() && child->type() != node_document);
            if (first_node())
            {
                child->m_next_sibling = m_first_node;
                m_first_node->m_prev_sibling = child;
            }
            else
            {
                child->m_next_sibling = 0;
                m_last_node = child;
            }
            m_first_node = child;
            child->m_parent = this;
            child->m_prev_sibling = 0;
        }   
        void append_node(xml_node<Ch> *child)
        {
            assert(child && !child->parent() && child->type() != node_document);
            if (first_node())
            {
                child->m_prev_sibling = m_last_node;
                m_last_node->m_next_sibling = child;
            }
            else
            {
                child->m_prev_sibling = 0;
                m_first_node = child;
            }
            m_last_node = child;
            child->m_parent = this;
            child->m_next_sibling = 0;
        }    
        void insert_node(xml_node<Ch> *where, xml_node<Ch> *child)
        {
            assert(!where || where->parent() == this);
            assert(child && !child->parent() && child->type() != node_document);
            if (where == m_first_node)
                prepend_node(child);
            else if (where == 0)
                append_node(child);
            else
            {
                child->m_prev_sibling = where->m_prev_sibling;
                child->m_next_sibling = where;
                where->m_prev_sibling->m_next_sibling = child;
                where->m_prev_sibling = child;
                child->m_parent = this;
            }
        }   
        void remove_first_node()
        {
            assert(first_node());
            xml_node<Ch> *child = m_first_node;
            m_first_node = child->m_next_sibling;
            if (child->m_next_sibling)
                child->m_next_sibling->m_prev_sibling = 0;
            else
                m_last_node = 0;
            child->m_parent = 0;
        }   
        void remove_last_node()
        {
            assert(first_node());
            xml_node<Ch> *child = m_last_node;
            if (child->m_prev_sibling)
            {
                m_last_node = child->m_prev_sibling;
                child->m_prev_sibling->m_next_sibling = 0;
            }
            else
                m_first_node = 0;
            child->m_parent = 0;
        }  
        void remove_node(xml_node<Ch> *where)
        {
            assert(where && where->parent() == this);
            assert(first_node());
            if (where == m_first_node)
                remove_first_node();
            else if (where == m_last_node)
                remove_last_node();
            else
            {
                where->m_prev_sibling->m_next_sibling = where->m_next_sibling;
                where->m_next_sibling->m_prev_sibling = where->m_prev_sibling;
                where->m_parent = 0;
            }
        } 
        void remove_all_nodes()
        {
            for (xml_node<Ch> *node = first_node(); node; node = node->m_next_sibling)
                node->m_parent = 0;
            m_first_node = 0;
        }  
        void prepend_attribute(xml_attribute<Ch> *attribute)
        {
            assert(attribute && !attribute->parent());
            if (first_attribute())
            {
                attribute->m_next_attribute = m_first_attribute;
                m_first_attribute->m_prev_attribute = attribute;
            }
            else
            {
                attribute->m_next_attribute = 0;
                m_last_attribute = attribute;
            }
            m_first_attribute = attribute;
            attribute->m_parent = this;
            attribute->m_prev_attribute = 0;
        }  
        void append_attribute(xml_attribute<Ch> *attribute)
        {
            assert(attribute && !attribute->parent());
            if (first_attribute())
            {
                attribute->m_prev_attribute = m_last_attribute;
                m_last_attribute->m_next_attribute = attribute;
            }
            else
            {
                attribute->m_prev_attribute = 0;
                m_first_attribute = attribute;
            }
            m_last_attribute = attribute;
            attribute->m_parent = this;
            attribute->m_next_attribute = 0;
        }    
        void insert_attribute(xml_attribute<Ch> *where, xml_attribute<Ch> *attribute)
        {
            assert(!where || where->parent() == this);
            assert(attribute && !attribute->parent());
            if (where == m_first_attribute)
                prepend_attribute(attribute);
            else if (where == 0)
                append_attribute(attribute);
            else
            {
                attribute->m_prev_attribute = where->m_prev_attribute;
                attribute->m_next_attribute = where;
                where->m_prev_attribute->m_next_attribute = attribute;
                where->m_prev_attribute = attribute;
                attribute->m_parent = this;
            }
        }   
        void remove_first_attribute()
        {
            assert(first_attribute());
            xml_attribute<Ch> *attribute = m_first_attribute;
            if (attribute->m_next_attribute)
            {
                attribute->m_next_attribute->m_prev_attribute = 0;
            }
            else
                m_last_attribute = 0;
            attribute->m_parent = 0;
            m_first_attribute = attribute->m_next_attribute;
        }   
        void remove_last_attribute()
        {
            assert(first_attribute());
            xml_attribute<Ch> *attribute = m_last_attribute;
            if (attribute->m_prev_attribute)
            {
                attribute->m_prev_attribute->m_next_attribute = 0;
                m_last_attribute = attribute->m_prev_attribute;
            }
            else
                m_first_attribute = 0;
            attribute->m_parent = 0;
        }  
        void remove_attribute(xml_attribute<Ch> *where)
        {
            assert(first_attribute() && where->parent() == this);
            if (where == m_first_attribute)
                remove_first_attribute();
            else if (where == m_last_attribute)
                remove_last_attribute();
            else
            {
                where->m_prev_attribute->m_next_attribute = where->m_next_attribute;
                where->m_next_attribute->m_prev_attribute = where->m_prev_attribute;
                where->m_parent = 0;
            }
        } 
        void remove_all_attributes()
        {
            for (xml_attribute<Ch> *attribute = first_attribute(); attribute; attribute = attribute->m_next_attribute)
                attribute->m_parent = 0;
            m_first_attribute = 0;
        }
        
    private:   
        xml_node(const xml_node &);
        void operator =(const xml_node &);          

        node_type m_type; 
        xml_node<Ch> *m_first_node; 
        xml_node<Ch> *m_last_node; 
        xml_attribute<Ch> *m_first_attribute; 
        xml_attribute<Ch> *m_last_attribute; 
        xml_node<Ch> *m_prev_sibling; 
        xml_node<Ch> *m_next_sibling; 

    };         
    template<class Ch = char>
    class xml_document: public xml_node<Ch>, public memory_pool<Ch>
    {
    
    public: 
        xml_document()
            : xml_node<Ch>(node_document)
        {
        }           
        template<int Flags>
        void parse(Ch *text)
        {
            assert(text); 
            this->remove_all_nodes();
            this->remove_all_attributes(); 
            parse_bom<Flags>(text); 
            while (1)
            { 
                skip<whitespace_pred, Flags>(text);
                if (*text == 0)
                    break; 
                if (*text == Ch('<'))
                {
                    ++text; 
                    if (xml_node<Ch> *node = parse_node<Flags>(text))
                        this->append_node(node);
                }
                else
                    RAPIDXML_PARSE_ERROR("expected <", text);
            }

        }  
        void clear()
        {
            this->remove_all_nodes();
            this->remove_all_attributes();
            memory_pool<Ch>::clear();
        }
        
    private:   
        struct whitespace_pred
        {
            static unsigned char test(Ch ch)
            {
                return internal::lookup_tables<0>::lookup_whitespace[static_cast<unsigned char>(ch)];
            }
        }; 
        struct node_name_pred
        {
            static unsigned char test(Ch ch)
            {
                return internal::lookup_tables<0>::lookup_node_name[static_cast<unsigned char>(ch)];
            }
        }; 
        struct attribute_name_pred
        {
            static unsigned char test(Ch ch)
            {
                return internal::lookup_tables<0>::lookup_attribute_name[static_cast<unsigned char>(ch)];
            }
        }; 
        struct text_pred
        {
            static unsigned char test(Ch ch)
            {
                return internal::lookup_tables<0>::lookup_text[static_cast<unsigned char>(ch)];
            }
        }; 
        struct text_pure_no_ws_pred
        {
            static unsigned char test(Ch ch)
            {
                return internal::lookup_tables<0>::lookup_text_pure_no_ws[static_cast<unsigned char>(ch)];
            }
        }; 
        struct text_pure_with_ws_pred
        {
            static unsigned char test(Ch ch)
            {
                return internal::lookup_tables<0>::lookup_text_pure_with_ws[static_cast<unsigned char>(ch)];
            }
        }; 
        template<Ch Quote>
        struct attribute_value_pred
        {
            static unsigned char test(Ch ch)
            {
                if (Quote == Ch('\''))
                    return internal::lookup_tables<0>::lookup_attribute_data_1[static_cast<unsigned char>(ch)];
                if (Quote == Ch('\"'))
                    return internal::lookup_tables<0>::lookup_attribute_data_2[static_cast<unsigned char>(ch)];
                return 0; 
            }
        }; 
        template<Ch Quote>
        struct attribute_value_pure_pred
        {
            static unsigned char test(Ch ch)
            {
                if (Quote == Ch('\''))
                    return internal::lookup_tables<0>::lookup_attribute_data_1_pure[static_cast<unsigned char>(ch)];
                if (Quote == Ch('\"'))
                    return internal::lookup_tables<0>::lookup_attribute_data_2_pure[static_cast<unsigned char>(ch)];
                return 0; 
            }
        }; 
        template<int Flags>
        static void insert_coded_character(Ch *&text, unsigned long code)
        {
            if (Flags & parse_no_utf8)
            {  
                text[0] = static_cast<unsigned char>(code);
                text += 1;
            }
            else
            { 
                if (code < 0x80) 
                {
	                text[0] = static_cast<unsigned char>(code);
                    text += 1;
                }
                else if (code < 0x800) 
                {
	                text[1] = static_cast<unsigned char>((code | 0x80) & 0xBF); code >>= 6;
	                text[0] = static_cast<unsigned char>(code | 0xC0);
                    text += 2;
                }
	            else if (code < 0x10000) 
                {
	                text[2] = static_cast<unsigned char>((code | 0x80) & 0xBF); code >>= 6;
	                text[1] = static_cast<unsigned char>((code | 0x80) & 0xBF); code >>= 6;
	                text[0] = static_cast<unsigned char>(code | 0xE0);
                    text += 3;
                }
	            else if (code < 0x110000) 
                {
	                text[3] = static_cast<unsigned char>((code | 0x80) & 0xBF); code >>= 6;
	                text[2] = static_cast<unsigned char>((code | 0x80) & 0xBF); code >>= 6;
	                text[1] = static_cast<unsigned char>((code | 0x80) & 0xBF); code >>= 6;
	                text[0] = static_cast<unsigned char>(code | 0xF0);
                    text += 4;
                }
                else 
                {
                    RAPIDXML_PARSE_ERROR("invalid numeric character entity", text);
                }
            }
        } 
        template<class StopPred, int Flags>
        static void skip(Ch *&text)
        {
            Ch *tmp = text;
            while (StopPred::test(*tmp))
                ++tmp;
            text = tmp;
        }   
        template<class StopPred, class StopPredPure, int Flags>
        static Ch *skip_and_expand_character_refs(Ch *&text)
        { 
            if (Flags & parse_no_entity_translation && 
                !(Flags & parse_normalize_whitespace) &&
                !(Flags & parse_trim_whitespace))
            {
                skip<StopPred, Flags>(text);
                return text;
            } 
            skip<StopPredPure, Flags>(text); 
            Ch *src = text;
            Ch *dest = src;
            while (StopPred::test(*src))
            { 
                if (!(Flags & parse_no_entity_translation))
                { 
                    if (src[0] == Ch('&'))
                    {
                        switch (src[1])
                        { 
                        case Ch('a'): 
                            if (src[2] == Ch('m') && src[3] == Ch('p') && src[4] == Ch(';'))
                            {
                                *dest = Ch('&');
                                ++dest;
                                src += 5;
                                continue;
                            }
                            if (src[2] == Ch('p') && src[3] == Ch('o') && src[4] == Ch('s') && src[5] == Ch(';'))
                            {
                                *dest = Ch('\'');
                                ++dest;
                                src += 6;
                                continue;
                            }
                            break; 
                        case Ch('q'): 
                            if (src[2] == Ch('u') && src[3] == Ch('o') && src[4] == Ch('t') && src[5] == Ch(';'))
                            {
                                *dest = Ch('"');
                                ++dest;
                                src += 6;
                                continue;
                            }
                            break; 
                        case Ch('g'): 
                            if (src[2] == Ch('t') && src[3] == Ch(';'))
                            {
                                *dest = Ch('>');
                                ++dest;
                                src += 4;
                                continue;
                            }
                            break; 
                        case Ch('l'): 
                            if (src[2] == Ch('t') && src[3] == Ch(';'))
                            {
                                *dest = Ch('<');
                                ++dest;
                                src += 4;
                                continue;
                            }
                            break; 
                        case Ch('#'): 
                            if (src[2] == Ch('x'))
                            {
                                unsigned long code = 0;
                                src += 3; 
                                while (1)
                                {
                                    unsigned char digit = internal::lookup_tables<0>::lookup_digits[static_cast<unsigned char>(*src)];
                                    if (digit == 0xFF)
                                        break;
                                    code = code * 16 + digit;
                                    ++src;
                                }
                                insert_coded_character<Flags>(dest, code); 
                            }
                            else
                            {
                                unsigned long code = 0;
                                src += 2; 
                                while (1)
                                {
                                    unsigned char digit = internal::lookup_tables<0>::lookup_digits[static_cast<unsigned char>(*src)];
                                    if (digit == 0xFF)
                                        break;
                                    code = code * 10 + digit;
                                    ++src;
                                }
                                insert_coded_character<Flags>(dest, code); 
                            }
                            if (*src == Ch(';'))
                                ++src;
                            else
                                RAPIDXML_PARSE_ERROR("expected ;", src);
                            continue; 
                        default: 
                            break;

                        }
                    }
                } 
                if (Flags & parse_normalize_whitespace)
                { 
                    if (whitespace_pred::test(*src))
                    {
                        *dest = Ch(' '); ++dest; 
                        ++src;  
                        while (whitespace_pred::test(*src))
                            ++src;
                        continue;
                    }
                } 
                *dest++ = *src++;

            } 
            text = src;
            return dest;

        }   
        template<int Flags>
        void parse_bom(Ch *&text)
        { 
            if (static_cast<unsigned char>(text[0]) == 0xEF && 
                static_cast<unsigned char>(text[1]) == 0xBB && 
                static_cast<unsigned char>(text[2]) == 0xBF)
            {
                text += 3; 
            }
        } 
        template<int Flags>
        xml_node<Ch> *parse_xml_declaration(Ch *&text)
        { 
            if (!(Flags & parse_declaration_node))
            { 
                while (text[0] != Ch('?') || text[1] != Ch('>'))
                {
                    if (!text[0])
                        RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                    ++text;
                }
                text += 2; 
                return 0;
            } 
            xml_node<Ch> *declaration = this->allocate_node(node_declaration); 
            skip<whitespace_pred, Flags>(text); 
            parse_node_attributes<Flags>(text, declaration); 
            if (text[0] != Ch('?') || text[1] != Ch('>'))
                RAPIDXML_PARSE_ERROR("expected ?>", text);
            text += 2;
            
            return declaration;
        } 
        template<int Flags>
        xml_node<Ch> *parse_comment(Ch *&text)
        { 
            if (!(Flags & parse_comment_nodes))
            { 
                while (text[0] != Ch('-') || text[1] != Ch('-') || text[2] != Ch('>'))
                {
                    if (!text[0])
                        RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                    ++text;
                }
                text += 3; 
                return 0; 
            } 
            Ch *value = text; 
            while (text[0] != Ch('-') || text[1] != Ch('-') || text[2] != Ch('>'))
            {
                if (!text[0])
                    RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                ++text;
            } 
            xml_node<Ch> *comment = this->allocate_node(node_comment);
            comment->value(value, text - value); 
            if (!(Flags & parse_no_string_terminators))
                *text = Ch('\0');
            
            text += 3; 
            return comment;
        } 
        template<int Flags>
        xml_node<Ch> *parse_doctype(Ch *&text)
        { 
            Ch *value = text; 
            while (*text != Ch('>'))
            { 
                switch (*text)
                {  
                case Ch('['):
                {
                    ++text; 
                    int depth = 1;
                    while (depth > 0)
                    {
                        switch (*text)
                        {
                            case Ch('['): ++depth; break;
                            case Ch(']'): --depth; break;
                            case 0: RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                        }
                        ++text;
                    }
                    break;
                } 
                case Ch('\0'):
                    RAPIDXML_PARSE_ERROR("unexpected end of data", text); 
                default:
                    ++text;

                }
            } 
            if (Flags & parse_doctype_node)
            { 
                xml_node<Ch> *doctype = this->allocate_node(node_doctype);
                doctype->value(value, text - value); 
                if (!(Flags & parse_no_string_terminators))
                    *text = Ch('\0');

                text += 1; 
                return doctype;
            }
            else
            {
                text += 1; 
                return 0;
            }

        } 
        template<int Flags>
        xml_node<Ch> *parse_pi(Ch *&text)
        { 
            if (Flags & parse_pi_nodes)
            { 
                xml_node<Ch> *pi = this->allocate_node(node_pi); 
                Ch *name = text;
                skip<node_name_pred, Flags>(text);
                if (text == name)
                    RAPIDXML_PARSE_ERROR("expected PI target", text);
                pi->name(name, text - name); 
                skip<whitespace_pred, Flags>(text); 
                Ch *value = text; 
                while (text[0] != Ch('?') || text[1] != Ch('>'))
                {
                    if (*text == Ch('\0'))
                        RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                    ++text;
                } 
                pi->value(value, text - value); 
                if (!(Flags & parse_no_string_terminators))
                {
                    pi->name()[pi->name_size()] = Ch('\0');
                    pi->value()[pi->value_size()] = Ch('\0');
                }
                
                text += 2; 
                return pi;
            }
            else
            { 
                while (text[0] != Ch('?') || text[1] != Ch('>'))
                {
                    if (*text == Ch('\0'))
                        RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                    ++text;
                }
                text += 2; 
                return 0;
            }
        }   
        template<int Flags>
        Ch parse_and_append_data(xml_node<Ch> *node, Ch *&text, Ch *contents_start)
        { 
            if (!(Flags & parse_trim_whitespace))
                text = contents_start; 
            Ch *value = text, *end;
            if (Flags & parse_normalize_whitespace)
                end = skip_and_expand_character_refs<text_pred, text_pure_with_ws_pred, Flags>(text);   
            else
                end = skip_and_expand_character_refs<text_pred, text_pure_no_ws_pred, Flags>(text); 
            if (Flags & parse_trim_whitespace)
            {
                if (Flags & parse_normalize_whitespace)
                { 
                    if (*(end - 1) == Ch(' '))
                        --end;
                }
                else
                { 
                    while (whitespace_pred::test(*(end - 1)))
                        --end;
                }
            }  
            if (!(Flags & parse_no_data_nodes))
            {
                xml_node<Ch> *data = this->allocate_node(node_data);
                data->value(value, end - value);
                node->append_node(data);
            } 
            if (!(Flags & parse_no_element_values)) 
                if (*node->value() == Ch('\0'))
                    node->value(value, end - value); 
            if (!(Flags & parse_no_string_terminators))
            {
                Ch ch = *text;
                *end = Ch('\0');
                return ch; 
            } 
            return *text;
        } 
        template<int Flags>
        xml_node<Ch> *parse_cdata(Ch *&text)
        { 
            if (Flags & parse_no_data_nodes)
            { 
                while (text[0] != Ch(']') || text[1] != Ch(']') || text[2] != Ch('>'))
                {
                    if (!text[0])
                        RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                    ++text;
                }
                text += 3; 
                return 0; 
            } 
            Ch *value = text;
            while (text[0] != Ch(']') || text[1] != Ch(']') || text[2] != Ch('>'))
            {
                if (!text[0])
                    RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                ++text;
            } 
            xml_node<Ch> *cdata = this->allocate_node(node_cdata);
            cdata->value(value, text - value); 
            if (!(Flags & parse_no_string_terminators))
                *text = Ch('\0');

            text += 3; 
            return cdata;
        } 
        template<int Flags>
        xml_node<Ch> *parse_element(Ch *&text)
        { 
            xml_node<Ch> *element = this->allocate_node(node_element); 
            Ch *name = text;
            skip<node_name_pred, Flags>(text);
            if (text == name)
                RAPIDXML_PARSE_ERROR("expected element name", text);
            element->name(name, text - name); 
            skip<whitespace_pred, Flags>(text); 
            parse_node_attributes<Flags>(text, element); 
            if (*text == Ch('>'))
            {
                ++text;
                parse_node_contents<Flags>(text, element);
            }
            else if (*text == Ch('/'))
            {
                ++text;
                if (*text != Ch('>'))
                    RAPIDXML_PARSE_ERROR("expected >", text);
                ++text;
            }
            else
                RAPIDXML_PARSE_ERROR("expected >", text); 
            if (!(Flags & parse_no_string_terminators))
                element->name()[element->name_size()] = Ch('\0'); 
            return element;
        } 
        template<int Flags>
        xml_node<Ch> *parse_node(Ch *&text)
        { 
            switch (text[0])
            { 
            default: 
                return parse_element<Flags>(text); 
            case Ch('?'): 
                ++text; 
                if ((text[0] == Ch('x') || text[0] == Ch('X')) &&
                    (text[1] == Ch('m') || text[1] == Ch('M')) && 
                    (text[2] == Ch('l') || text[2] == Ch('L')) &&
                    whitespace_pred::test(text[3]))
                { 
                    text += 4; 
                    return parse_xml_declaration<Flags>(text);
                }
                else
                { 
                    return parse_pi<Flags>(text);
                } 
            case Ch('!'): 
                switch (text[1])    
                { 
                case Ch('-'):
                    if (text[2] == Ch('-'))
                    { 
                        text += 3; 
                        return parse_comment<Flags>(text);
                    }
                    break; 
                case Ch('['):
                    if (text[2] == Ch('C') && text[3] == Ch('D') && text[4] == Ch('A') && 
                        text[5] == Ch('T') && text[6] == Ch('A') && text[7] == Ch('['))
                    { 
                        text += 8; 
                        return parse_cdata<Flags>(text);
                    }
                    break; 
                case Ch('D'):
                    if (text[2] == Ch('O') && text[3] == Ch('C') && text[4] == Ch('T') && 
                        text[5] == Ch('Y') && text[6] == Ch('P') && text[7] == Ch('E') && 
                        whitespace_pred::test(text[8]))
                    { 
                        text += 9; 
                        return parse_doctype<Flags>(text);
                    }

                }  
                ++text; 
                while (*text != Ch('>'))
                {
                    if (*text == 0)
                        RAPIDXML_PARSE_ERROR("unexpected end of data", text);
                    ++text;
                }
                ++text; 
                return 0; 

            }
        } 
        template<int Flags>
        void parse_node_contents(Ch *&text, xml_node<Ch> *node)
        { 
            while (1)
            { 
                Ch *contents_start = text; 
                skip<whitespace_pred, Flags>(text);
                Ch next_char = *text;    
            after_data_node: 
                switch (next_char)
                { 
                case Ch('<'):
                    if (text[1] == Ch('/'))
                    { 
                        text += 2; 
                        if (Flags & parse_validate_closing_tags)
                        { 
                            Ch *closing_name = text;
                            skip<node_name_pred, Flags>(text);
                            if (!internal::compare(node->name(), node->name_size(), closing_name, text - closing_name, true))
                                RAPIDXML_PARSE_ERROR("invalid closing tag name", text);
                        }
                        else
                        { 
                            skip<node_name_pred, Flags>(text);
                        } 
                        skip<whitespace_pred, Flags>(text);
                        if (*text != Ch('>'))
                            RAPIDXML_PARSE_ERROR("expected >", text);
                        ++text; 
                        return; 
                    }
                    else
                    { 
                        ++text; 
                        if (xml_node<Ch> *child = parse_node<Flags>(text))
                            node->append_node(child);
                    }
                    break; 
                case Ch('\0'):
                    RAPIDXML_PARSE_ERROR("unexpected end of data", text); 
                default:
                    next_char = parse_and_append_data<Flags>(node, text, contents_start);
                    goto after_data_node; 

                }
            }
        } 
        template<int Flags>
        void parse_node_attributes(Ch *&text, xml_node<Ch> *node)
        { 
            while (attribute_name_pred::test(*text))
            { 
                Ch *name = text;
                ++text; 
                skip<attribute_name_pred, Flags>(text);
                if (text == name)
                    RAPIDXML_PARSE_ERROR("expected attribute name", name); 
                xml_attribute<Ch> *attribute = this->allocate_attribute();
                attribute->name(name, text - name);
                node->append_attribute(attribute); 
                skip<whitespace_pred, Flags>(text); 
                if (*text != Ch('='))
                    RAPIDXML_PARSE_ERROR("expected =", text);
                ++text; 
                if (!(Flags & parse_no_string_terminators))
                    attribute->name()[attribute->name_size()] = 0; 
                skip<whitespace_pred, Flags>(text); 
                Ch quote = *text;
                if (quote != Ch('\'') && quote != Ch('"'))
                    RAPIDXML_PARSE_ERROR("expected ' or \"", text);
                ++text; 
                Ch *value = text, *end;
                const int AttFlags = Flags & ~parse_normalize_whitespace; 
                if (quote == Ch('\''))
                    end = skip_and_expand_character_refs<attribute_value_pred<Ch('\'')>, attribute_value_pure_pred<Ch('\'')>, AttFlags>(text);
                else
                    end = skip_and_expand_character_refs<attribute_value_pred<Ch('"')>, attribute_value_pure_pred<Ch('"')>, AttFlags>(text); 
                attribute->value(value, end - value); 
                if (*text != quote)
                    RAPIDXML_PARSE_ERROR("expected ' or \"", text);
                ++text;  
                if (!(Flags & parse_no_string_terminators))
                    attribute->value()[attribute->value_size()] = 0; 
                skip<whitespace_pred, Flags>(text);
            }
        }

    }; 
    namespace internal
    { 
        template<int Dummy>
        const unsigned char lookup_tables<Dummy>::lookup_whitespace[256] = 
        { 
             0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  1,  0,  0, 
             0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
             1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
             0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
             0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
             0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
             0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
             0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
             0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
             0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
             0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
             0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
             0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
             0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
             0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
             0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 
        }; 
        template<int Dummy>
        const unsigned char lookup_tables<Dummy>::lookup_node_name[256] = 
        { 
             0,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  1,  0,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 
        }; 
        template<int Dummy>
        const unsigned char lookup_tables<Dummy>::lookup_text[256] = 
        { 
             0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 
        };  
        template<int Dummy>
        const unsigned char lookup_tables<Dummy>::lookup_text_pure_no_ws[256] = 
        { 
             0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 
        };  
        template<int Dummy>
        const unsigned char lookup_tables<Dummy>::lookup_text_pure_with_ws[256] = 
        { 
             0,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  1,  0,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             0,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 
        }; 
        template<int Dummy>
        const unsigned char lookup_tables<Dummy>::lookup_attribute_name[256] = 
        { 
             0,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  1,  1,  0,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 
        }; 
        template<int Dummy>
        const unsigned char lookup_tables<Dummy>::lookup_attribute_data_1[256] = 
        { 
             0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 
        }; 
        template<int Dummy>
        const unsigned char lookup_tables<Dummy>::lookup_attribute_data_1_pure[256] = 
        { 
             0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 
        }; 
        template<int Dummy>
        const unsigned char lookup_tables<Dummy>::lookup_attribute_data_2[256] = 
        { 
             0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 
        }; 
        template<int Dummy>
        const unsigned char lookup_tables<Dummy>::lookup_attribute_data_2_pure[256] = 
        { 
             0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  0,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 
             1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 
        }; 
        template<int Dummy>
        const unsigned char lookup_tables<Dummy>::lookup_digits[256] = 
        { 
           255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 
           255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 
           255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 
             0,  1,  2,  3,  4,  5,  6,  7,  8,  9,255,255,255,255,255,255, 
           255, 10, 11, 12, 13, 14, 15,255,255,255,255,255,255,255,255,255, 
           255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 
           255, 10, 11, 12, 13, 14, 15,255,255,255,255,255,255,255,255,255, 
           255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 
           255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 
           255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 
           255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 
           255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 
           255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 
           255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 
           255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255, 
           255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255 
        }; 
        template<int Dummy>
        const unsigned char lookup_tables<Dummy>::lookup_upcase[256] = 
        { 
           0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 
           16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 
           32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 
           48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 
           64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 
           80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 
           96, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 
           80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 123,124,125,126,127, 
           128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143, 
           144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159, 
           160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175, 
           176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191, 
           192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207, 
           208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223, 
           224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239, 
           240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255 
        };
    } 

} 
#undef RAPIDXML_PARSE_ERROR 
#ifdef _MSC_VER
    #pragma warning(pop)
#endif

#endif
