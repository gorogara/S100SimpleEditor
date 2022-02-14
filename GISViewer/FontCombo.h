// FontCombo.h : header file   

class CFontCombo : public CComboBox
{ 
public:
	CFontCombo(); 
public:   
	protected:
	virtual void PreSubclassWindow();  
public:
	BYTE required_charset;
	virtual ~CFontCombo();
	static int CALLBACK EnumFontFamExProc(
		ENUMLOGFONTEX *lpelfe,	
		NEWTEXTMETRICEX *lpntme,	
		int FontType,	
		LPARAM lParam); 
protected:   

	DECLARE_MESSAGE_MAP()

protected: 
	CStringList fontlist;
private:
	void ProcessFonts(void);
}; 
