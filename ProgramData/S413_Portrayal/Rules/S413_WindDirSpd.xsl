<?xml version="1.0" encoding="UTF-8"?>
<S100FC:S100_FC_FeatureCatalogue xmlns:S100FC="http://www.iho.int/S100FC" xmlns:S100Base="http://www.iho.int/S100Base" xmlns:S100CI="http://www.iho.int/S100CI" xmlns:xlink="http://www.w3.org/1999/xlink" xmlns:S100FD="http://www.iho.int/S100FD" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.iho.int/S100FC S100FC.xsd">
  <S100FC:name>Feature Catalogue for S-910</S100FC:name>
  <S100FC:scope>S-910(temporary numeric number) Fishery Information Chart</S100FC:scope>
  <S100FC:fieldOfApplication>Marine Navigation</S100FC:fieldOfApplication>
  <S100FC:versionNumber>1.0.0</S100FC:versionNumber>
  <S100FC:versionDate>2020-11-01</S100FC:versionDate>
  <S100FC:producer>
    <S100CI:role>pointOfContact</S100CI:role>
    <S100CI:party>
      <S100CI:CI_Organisation>
        <S100CI:name>KHOA</S100CI:name>
        <S100CI:contactInfo>
          <S100CI:address>
            <S100CI:administrativeArea>Busan</S100CI:administrativeArea>
            <S100CI:country>Republic of Korea</S100CI:country>
            <S100CI:electronicMailAddress>izzykim@korea.kr</S100CI:electronicMailAddress>
          </S100CI:address>
          <S100CI:onlineResource>
            <S100CI:linkage>www.khoa.go.kr</S100CI:linkage>
          </S100CI:onlineResource>
        </S100CI:contactInfo>
      </S100CI:CI_Organisation>
    </S100CI:party>
  </S100FC:producer>
  <S100FC:classification>unclassified</S100FC:classification>
  <S100FC:S100_FC_SimpleAttributes>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Display name</S100FC:name>
      <S100FC:definition>A statement expressing if a feature name is to be displayed in certain system display settings or not</S100FC:definition>
      <S100FC:code>displayName</S100FC:code>
      <S100FC:valueType>boolean</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Language</S100FC:name>
      <S100FC:definition>The method of human communication, either spoken or written, consisting of the use of words in a structured and conventional way</S100FC:definition>
      <S100FC:code>language</S100FC:code>
      <S100FC:remarks>(S-122)Remarks: The language is encoded by a character code following ISO 639-3</S100FC:remarks>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Name</S100FC:name>
      <S100FC:definition>The individual name of a feature.</S100FC:definition>
      <S100FC:code>name</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Date end</S100FC:name>
      <S100FC:definition>The latest date on which an object (e.g., a buoy) will be present.</S100FC:definition>
      <S100FC:code>dateEnd</S100FC:code>
      <S100FC:remarks>This attribute is to be used to indicate the removal or cancellation of an object at a specific date in the future. See also 'periodic date end' (PEREND).</S100FC:remarks>
      <S100FC:alias>DATEND</S100FC:alias>
      <S100FC:valueType>S100_TruncatedDate</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Date start</S100FC:name>
      <S100FC:definition>The earliest date on which an object (e.g., a buoy) will be present.</S100FC:definition>
      <S100FC:code>dateStart</S100FC:code>
      <S100FC:remarks>This attribute is to be used to indicate the deployment or implementation of an object at a specific date in the future. See also 'periodic date start' (PERSTA).</S100FC:remarks>
      <S100FC:alias>DATSTA</S100FC:alias>
      <S100FC:valueType>S100_TruncatedDate</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Category of authority</S100FC:name>
      <S100FC:definition>The type of person, government agency or organisation granted powers of managing or controlling access to and/or activity in an area</S100FC:definition>
      <S100FC:code>categoryOfAuthority</S100FC:code>
      <S100FC:alias>CATAUT</S100FC:alias>
      <S100FC:valueType>enumeration</S100FC:valueType>
      <S100FC:listedValues>
        <S100FC:listedValue>
          <S100FC:label>customs</S100FC:label>
          <S100FC:definition>The agency or establishment for collecting duties, tolls. (Merriam-Websters online Dictionary 23rd February 2006, amended).</S100FC:definition>
          <S100FC:code>1</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>border control</S100FC:label>
          <S100FC:definition>The administration to prevent or detect and prosecute violations of rules and regulations at international boundaries (adapted from Merriam-Websters online Dictionary 23rd February 2006).</S100FC:definition>
          <S100FC:code>2</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>police</S100FC:label>
          <S100FC:definition>The department of government, or civil force, charged with maintaining public order. (Adapted from OED)</S100FC:definition>
          <S100FC:code>3</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>port</S100FC:label>
          <S100FC:definition>Person or corporation, owners of, or entrusted with or invested with the power of managing a port. May be called a Harbour Board, Port Trust, Port Commission, Harbour Commission, Marine Department (NP 100 8th Edition 14 Oct 2004)</S100FC:definition>
          <S100FC:code>4</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>immigration</S100FC:label>
          <S100FC:definition>The authority controlling people entering a country.</S100FC:definition>
          <S100FC:code>5</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>health</S100FC:label>
          <S100FC:definition>The authority with responsibility for checking the validity of the health declaration of a vessel and for declaring free pratique.</S100FC:definition>
          <S100FC:code>6</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>coast guard</S100FC:label>
          <S100FC:definition>Organisation keeping watch on shipping and coastal waters according to governmental law; normally the authority with reponsibility for search and rescue.</S100FC:definition>
          <S100FC:code>7</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>agricultural</S100FC:label>
          <S100FC:definition>The authority with responsibility for preventing infection of the agriculture of a country and for the protection of the agricultural interests of a country.</S100FC:definition>
          <S100FC:code>8</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>military</S100FC:label>
          <S100FC:definition>A military authority which provides control of access to or approval for transit through designated areas or airspace.</S100FC:definition>
          <S100FC:code>9</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>private company</S100FC:label>
          <S100FC:definition>A private or publicly owned company or commercial enterprise which exercises control of facilities, for example a callibration area.</S100FC:definition>
          <S100FC:code>10</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>maritime police</S100FC:label>
          <S100FC:definition>A governmental or military force with jurisdiction in territorial waters. Examples could include Gendarmerie Maritime, Carabinierie, and Guardia Civil.</S100FC:definition>
          <S100FC:code>11</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>environmental</S100FC:label>
          <S100FC:definition>An authority with responsibility for the protection of the environment.</S100FC:definition>
          <S100FC:code>12</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>fishery</S100FC:label>
          <S100FC:definition>An authority with responsibility for the control of fisheries.</S100FC:definition>
          <S100FC:code>13</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>finance</S100FC:label>
          <S100FC:definition>an authority with responsibility for the control and movement of money.</S100FC:definition>
          <S100FC:code>14</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>maritime</S100FC:label>
          <S100FC:definition>A national or regional authority charged with administration of maritime affairs.</S100FC:definition>
          <S100FC:code>15</S100FC:code>
        </S100FC:listedValue>
      </S100FC:listedValues>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Country</S100FC:name>
      <S100FC:definition>The name of a nation. (Adapted from The American Heritage Dictionaries)</S100FC:definition>
      <S100FC:code>country</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Reported date</S100FC:name>
      <S100FC:definition>The date that the item was observed, done, or investigated</S100FC:definition>
      <S100FC:code>reportedDate</S100FC:code>
      <S100FC:valueType>S100_TruncatedDate</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Source</S100FC:name>
      <S100FC:definition>An identifier (publication, document, reference work, instrument, vessel, etc) from which information comes or is acquired.</S100FC:definition>
      <S100FC:code>source</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Source type</S100FC:name>
      <S100FC:definition>type of the source</S100FC:definition>
      <S100FC:code>sourceType</S100FC:code>
      <S100FC:valueType>enumeration</S100FC:valueType>
      <S100FC:listedValues>
        <S100FC:listedValue>
          <S100FC:label>law or regulation</S100FC:label>
          <S100FC:definition>treaty, convention, or international agreement; law or regulation issued by a national or other authority</S100FC:definition>
          <S100FC:code>1</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>official publication</S100FC:label>
          <S100FC:definition>publication not having the force of law, issued by an international organisation or a national or local administration</S100FC:definition>
          <S100FC:code>2</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>mariner report, confirmed</S100FC:label>
          <S100FC:definition>Reported by mariner(s) and confirmed by another source</S100FC:definition>
          <S100FC:code>7</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>mariner report, not confirmed</S100FC:label>
          <S100FC:definition>reported by mariner(s) but not confirmed</S100FC:definition>
          <S100FC:code>8</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>industry publications and reports</S100FC:label>
          <S100FC:definition>shipping and other industry publication, including graphics, charts and web sites</S100FC:definition>
          <S100FC:code>9</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>remotely sensed images</S100FC:label>
          <S100FC:definition>information obtained from satellite images</S100FC:definition>
          <S100FC:code>10</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>photographs</S100FC:label>
          <S100FC:definition>
            information obtained from photographs
          </S100FC:definition>
          <S100FC:code>11</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>products issued by HO services</S100FC:label>
          <S100FC:definition>information obtained from products issued by Hydrographic Offices</S100FC:definition>
          <S100FC:code>12</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>news media</S100FC:label>
          <S100FC:definition>information obtained from news media</S100FC:definition>
          <S100FC:code>13</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>traffic data</S100FC:label>
          <S100FC:definition>information obtained from the analysis of traffic data</S100FC:definition>
          <S100FC:code>14</S100FC:code>
        </S100FC:listedValue>
      </S100FC:listedValues>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Category of text</S100FC:name>
      <S100FC:definition>Classification of completeness of textual information in relation to the source.</S100FC:definition>
      <S100FC:code>categoryOfText</S100FC:code>
      <S100FC:valueType>enumeration</S100FC:valueType>
      <S100FC:listedValues>
        <S100FC:listedValue>
          <S100FC:label>abstract or summary</S100FC:label>
          <S100FC:definition>A statement summarizing the important points of a text</S100FC:definition>
          <S100FC:code>1</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>extract</S100FC:label>
          <S100FC:definition>An excerpt or excerpts from a text</S100FC:definition>
          <S100FC:code>2</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>full text</S100FC:label>
          <S100FC:definition>The whole text</S100FC:definition>
          <S100FC:code>3</S100FC:code>
        </S100FC:listedValue>
      </S100FC:listedValues>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>File Locator</S100FC:name>
      <S100FC:definition>The string encodes the location of a fragment of text or other information in a support file.</S100FC:definition>
      <S100FC:code>fileLocator</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>File Reference</S100FC:name>
      <S100FC:definition>The string encodes the file name of an external text file that contains the text in English</S100FC:definition>
      <S100FC:code>fileReference</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Headline</S100FC:name>
      <S100FC:definition>Words set at the head of a passage or page to introduce or categorize</S100FC:definition>
      <S100FC:code>headline</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Text</S100FC:name>
      <S100FC:definition>A non-formatted digital text string</S100FC:definition>
      <S100FC:code>text</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Linkage</S100FC:name>
      <S100FC:definition>location (address) for on-line access using a URL/URI address or similar addressing scheme. (Adapted from ISO 19115:2014.)</S100FC:definition>
      <S100FC:code>linkage</S100FC:code>
      <S100FC:remarks>Adapted from ISO 19115:2014.</S100FC:remarks>
      <S100FC:valueType>URL</S100FC:valueType>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Protocol</S100FC:name>
      <S100FC:definition>connection protocol to be used. Example: ftp, http get KVP, http POST, etc.</S100FC:definition>
      <S100FC:code>protocol</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Application profile</S100FC:name>
      <S100FC:definition>name of an application profile that can be used with the online resource (ISO 19115)</S100FC:definition>
      <S100FC:code>applicationProfile</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Name of resource</S100FC:name>
      <S100FC:definition>Name of the online resource.</S100FC:definition>
      <S100FC:code>nameOfResource</S100FC:code>
      <S100FC:alias>NAMRES</S100FC:alias>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Online description</S100FC:name>
      <S100FC:definition>Detailed text description of what the online resource is/does</S100FC:definition>
      <S100FC:code>onlineDescription</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Online function</S100FC:name>
      <S100FC:definition>code for function performed by the online resource</S100FC:definition>
      <S100FC:code>onlineFunction</S100FC:code>
      <S100FC:remarks>codeListType=open enumeration; encoding=other: [something]</S100FC:remarks>
      <S100FC:valueType>S100_CodeList</S100FC:valueType>
      <S100FC:listedValues>
        <S100FC:listedValue>
          <S100FC:label>download</S100FC:label>
          <S100FC:definition>online instructions for transferring data from one storage device or system to another. (ISO 19115:2014)</S100FC:definition>
          <S100FC:code>1</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>information</S100FC:label>
          <S100FC:definition>online information about the resource (ISO 19115:2014)</S100FC:definition>
          <S100FC:code>2</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>offlineAccess</S100FC:label>
          <S100FC:definition>online instructions for requesting the resource from the provider (ISO 19115:2014)</S100FC:definition>
          <S100FC:code>3</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>order</S100FC:label>
          <S100FC:definition>online order process for obtaining the resource (ISO 19115:2014).</S100FC:definition>
          <S100FC:code>4</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>search</S100FC:label>
          <S100FC:definition>online search interface for seeking out information about the resource (ISO 19115:2014).</S100FC:definition>
          <S100FC:code>5</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>completeMetadata</S100FC:label>
          <S100FC:definition>complete metadata provided (ISO 19115:2014).</S100FC:definition>
          <S100FC:code>6</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>browseGraphic</S100FC:label>
          <S100FC:definition>browse graphic provided (ISO 19115:2014).</S100FC:definition>
          <S100FC:code>7</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>upload</S100FC:label>
          <S100FC:definition>online resource upload capability provided (ISO 19115:2014).</S100FC:definition>
          <S100FC:code>8</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>emailService</S100FC:label>
          <S100FC:definition>online email service provided (ISO 19115:2014)</S100FC:definition>
          <S100FC:code>9</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>browsing</S100FC:label>
          <S100FC:definition>online browsing provided (ISO 19115:2014)</S100FC:definition>
          <S100FC:code>10</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>fileAccess</S100FC:label>
          <S100FC:definition>online file access provided (ISO 19115:2014)</S100FC:definition>
          <S100FC:code>11</S100FC:code>
        </S100FC:listedValue>
      </S100FC:listedValues>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Protocol request</S100FC:name>
      <S100FC:definition>Request used to access the resource. Structure and content depend on the protocol and standard used by the online resource, such as Web Feature Service standard.</S100FC:definition>
      <S100FC:code>protocolRequest</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Communication channel</S100FC:name>
      <S100FC:definition>A channel number assigned to a specific radio frequency, frequencies or frequency band.</S100FC:definition>
      <S100FC:code>communicationChannel</S100FC:code>
      <S100FC:remarks>The expected input is the specific VHF-Channel. The attribute 'communication channel' encodes the various VHF-channels used for communication.</S100FC:remarks>
      <S100FC:alias>COMCHA</S100FC:alias>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Contact instructions</S100FC:name>
      <S100FC:definition>Instructions provided on how to contact a particular person, organisation or service.</S100FC:definition>
      <S100FC:code>contactInstructions</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Delivery point</S100FC:name>
      <S100FC:definition>Details  of where post can be delivered such as the apartment, name and/or number of a street, building or PO Box.</S100FC:definition>
      <S100FC:code>deliveryPoint</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>City name</S100FC:name>
      <S100FC:definition>The name of a town or city.</S100FC:definition>
      <S100FC:code>cityName</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Administrative Division</S100FC:name>
      <S100FC:definition>Administrative division is a generic term for an administrative region within a country at a level below that of the sovereign state.</S100FC:definition>
      <S100FC:code>administrativeDivision</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Postal code</S100FC:name>
      <S100FC:definition>Known in various countries as a postcode, or ZIP code, the postal code is a series of letters and/or digits that identifies each postal delivery area.</S100FC:definition>
      <S100FC:code>postalCode</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Fishery Location</S100FC:name>
      <S100FC:definition>Fishery Location</S100FC:definition>
      <S100FC:code>fisheryLocation</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Fishery Right</S100FC:name>
      <S100FC:definition>Fishery Right</S100FC:definition>
      <S100FC:code>fisheryRight</S100FC:code>
      <S100FC:valueType>S100_CodeList</S100FC:valueType>
      <S100FC:listedValues>
        <S100FC:listedValue>
          <S100FC:label>local fishing</S100FC:label>
          <S100FC:definition>local fishing</S100FC:definition>
          <S100FC:code>1</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>farm culture</S100FC:label>
          <S100FC:definition>farm culture</S100FC:definition>
          <S100FC:code>2</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>fixed net fishing</S100FC:label>
          <S100FC:definition>fixed net fishing</S100FC:definition>
          <S100FC:code>3</S100FC:code>
        </S100FC:listedValue>
      </S100FC:listedValues>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Fishing Method</S100FC:name>
      <S100FC:definition>Fishing Method</S100FC:definition>
      <S100FC:code>fishingMethod</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>License Number</S100FC:name>
      <S100FC:definition>License Number</S100FC:definition>
      <S100FC:code>licenseNumber</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Scale Minimum</S100FC:name>
      <S100FC:definition>Scale Minimum</S100FC:definition>
      <S100FC:code>scaleMinimum</S100FC:code>
      <S100FC:valueType>integer</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Status</S100FC:name>
      <S100FC:definition>
        The condition of an object at a given instant in
        time.
      </S100FC:definition>
      <S100FC:code>status</S100FC:code>
      <S100FC:alias>STATUS</S100FC:alias>
      <S100FC:valueType>enumeration</S100FC:valueType>
      <S100FC:listedValues>
        <S100FC:listedValue>
          <S100FC:label>permanent</S100FC:label>
          <S100FC:definition>
            intended to last or function
            indefinitely.
          </S100FC:definition>
          <S100FC:code>1</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>occasional</S100FC:label>
          <S100FC:definition>
            acting on special occasions happening
            irregularly.
          </S100FC:definition>
          <S100FC:code>2</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>recommended</S100FC:label>
          <S100FC:definition>
            presented as worthy of confidence, acceptance, use,
            etc.
          </S100FC:definition>
          <S100FC:code>3</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>not in use</S100FC:label>
          <S100FC:definition>
            no longer used for the purpose intended
            disused.
          </S100FC:definition>
          <S100FC:code>4</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>periodic/intermittent</S100FC:label>
          <S100FC:definition>recurring at intervals.</S100FC:definition>
          <S100FC:code>5</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>reserved</S100FC:label>
          <S100FC:definition>set apart for some specific use.</S100FC:definition>
          <S100FC:code>6</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>temporary</S100FC:label>
          <S100FC:definition>meant to last only for a time.</S100FC:definition>
          <S100FC:code>7</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>private</S100FC:label>
          <S100FC:definition>not in public ownership or operation.</S100FC:definition>
          <S100FC:code>8</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>mandatory</S100FC:label>
          <S100FC:definition>compulsory enforced.</S100FC:definition>
          <S100FC:code>9</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>extinguished</S100FC:label>
          <S100FC:definition>no longer lit</S100FC:definition>
          <S100FC:code>11</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>illuminated</S100FC:label>
          <S100FC:definition>lit by floodlights, strip lights, etc.</S100FC:definition>
          <S100FC:code>12</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>historic</S100FC:label>
          <S100FC:definition>famous in history of historical interest.</S100FC:definition>
          <S100FC:code>13</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>public</S100FC:label>
          <S100FC:definition>
            belonging to, available to, used or shared by, the community
            as a whole and not restricted to private use.
          </S100FC:definition>
          <S100FC:code>14</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>synchronized</S100FC:label>
          <S100FC:definition>
            occur at a time, coincide in point of time, be contemporary
            or simultaneous.
          </S100FC:definition>
          <S100FC:code>15</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>watched</S100FC:label>
          <S100FC:definition>
            looked at or observed over a period of time especially so as
            to be aware of any movement or change.
          </S100FC:definition>
          <S100FC:code>16</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>un-watched</S100FC:label>
          <S100FC:definition>
            usually automatic in operation, without any
            permanently-stationed personnel to superintend it.
          </S100FC:definition>
          <S100FC:code>17</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>existence doubtful</S100FC:label>
          <S100FC:definition>
            an object that has been reported but has not been definitely
            determined to exist.
          </S100FC:definition>
          <S100FC:code>18</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>buoyed</S100FC:label>
          <S100FC:definition>Marked by buoys</S100FC:definition>
          <S100FC:code>28</S100FC:code>
        </S100FC:listedValue>
      </S100FC:listedValues>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Type Of Culture</S100FC:name>
      <S100FC:definition>Type Of Culture</S100FC:definition>
      <S100FC:code>typeOfCulture</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Vertical Length</S100FC:name>
      <S100FC:definition>Vertical Length</S100FC:definition>
      <S100FC:code>verticalLength</S100FC:code>
      <S100FC:valueType>real</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Category Of FishingFacility</S100FC:name>
      <S100FC:definition>Category Of FishingFacility</S100FC:definition>
      <S100FC:code>categoryOfFishingFacility</S100FC:code>
      <S100FC:valueType>enumeration</S100FC:valueType>
      <S100FC:listedValues>
        <S100FC:listedValue>
          <S100FC:label>fishing stake</S100FC:label>
          <S100FC:definition>fishing stake</S100FC:definition>
          <S100FC:code>1</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>fish trap</S100FC:label>
          <S100FC:definition>fish trap</S100FC:definition>
          <S100FC:code>2</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>fish weir</S100FC:label>
          <S100FC:definition>fish weir</S100FC:definition>
          <S100FC:code>3</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>tunny net</S100FC:label>
          <S100FC:definition>tunny net</S100FC:definition>
          <S100FC:code>4</S100FC:code>
        </S100FC:listedValue>
      </S100FC:listedValues>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Condition</S100FC:name>
      <S100FC:definition>Condition</S100FC:definition>
      <S100FC:code>condition</S100FC:code>
      <S100FC:valueType>enumeration</S100FC:valueType>
      <S100FC:listedValues>
        <S100FC:listedValue>
          <S100FC:label>under construction</S100FC:label>
          <S100FC:definition>under construction</S100FC:definition>
          <S100FC:code>1</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>ruined</S100FC:label>
          <S100FC:definition>ruined</S100FC:definition>
          <S100FC:code>2</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>planned construction</S100FC:label>
          <S100FC:definition>planned construction</S100FC:definition>
          <S100FC:code>3</S100FC:code>
        </S100FC:listedValue>
      </S100FC:listedValues>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Category Of Marine Farm Culture</S100FC:name>
      <S100FC:definition>Category Of Marine Farm Culture</S100FC:definition>
      <S100FC:code>categoryOfMarineFarmCulture</S100FC:code>
      <S100FC:valueType>enumeration</S100FC:valueType>
      <S100FC:listedValues>
        <S100FC:listedValue>
          <S100FC:label>crustaceans</S100FC:label>
          <S100FC:definition>crustaceans</S100FC:definition>
          <S100FC:code>1</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>edible divale molluscs</S100FC:label>
          <S100FC:definition>edible divale molluscs</S100FC:definition>
          <S100FC:code>2</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>fish</S100FC:label>
          <S100FC:definition>fish</S100FC:definition>
          <S100FC:code>3</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>seaweed</S100FC:label>
          <S100FC:definition>seaweed</S100FC:definition>
          <S100FC:code>4</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>pearl culture farm</S100FC:label>
          <S100FC:definition>pearl culture farm</S100FC:definition>
          <S100FC:code>5</S100FC:code>
        </S100FC:listedValue>
      </S100FC:listedValues>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Exposition Of Sounding</S100FC:name>
      <S100FC:definition>Exposition Of Sounding</S100FC:definition>
      <S100FC:code>expositionOfSounding</S100FC:code>
      <S100FC:valueType>enumeration</S100FC:valueType>
      <S100FC:listedValues>
        <S100FC:listedValue>
          <S100FC:label>within the range of depth of the surrounding depth area</S100FC:label>
          <S100FC:definition>within the range of depth of the surrounding depth area</S100FC:definition>
          <S100FC:code>1</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>shoaler than the range of depth od the surroungding depth area</S100FC:label>
          <S100FC:definition>shoaler than the range of depth od the surroungding depth area</S100FC:definition>
          <S100FC:code>2</S100FC:code>
        </S100FC:listedValue>
      </S100FC:listedValues>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Quality Of Vertical Measurement</S100FC:name>
      <S100FC:definition>Quality Of Vertical Measurement</S100FC:definition>
      <S100FC:code>qualityOfVerticalMeasurement</S100FC:code>
      <S100FC:valueType>enumeration</S100FC:valueType>
      <S100FC:listedValues>
        <S100FC:listedValue>
          <S100FC:label>depth known</S100FC:label>
          <S100FC:definition>depth known</S100FC:definition>
          <S100FC:code>1</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>depth or least depth unknown</S100FC:label>
          <S100FC:definition>depth or least depth unknown</S100FC:definition>
          <S100FC:code>2</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>doubtful sounding</S100FC:label>
          <S100FC:definition>doubtful sounding</S100FC:definition>
          <S100FC:code>3</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>unrealiable sounding</S100FC:label>
          <S100FC:definition>unrealiable sounding</S100FC:definition>
          <S100FC:code>4</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>least depth known</S100FC:label>
          <S100FC:definition>least depth known</S100FC:definition>
          <S100FC:code>6</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>least depth unknown, safe clearance at value shown</S100FC:label>
          <S100FC:definition>least depth unknown, safe clearance at value shown</S100FC:definition>
          <S100FC:code>7</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>value reported(not surveyed)</S100FC:label>
          <S100FC:definition>value reported(not surveyed)</S100FC:definition>
          <S100FC:code>8</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>value reported(not confirmed)</S100FC:label>
          <S100FC:definition>value reported(not confirmed)</S100FC:definition>
          <S100FC:code>9</S100FC:code>
        </S100FC:listedValue>
      </S100FC:listedValues>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Restriction</S100FC:name>
      <S100FC:definition>
        The official legal statute of each kind of restricted
        area.
      </S100FC:definition>
      <S100FC:code>restriction</S100FC:code>
      <S100FC:remarks>
        Defines the kind of restriction(s), e.g., the restriction for 'a game
        preserve' may be 'entry prohibited', the restriction for an 'anchoring prohibition'
        is 'anchoring prohibited'. The complete information about the restriction(s),
        actually held in handbooks or other publications, may be encoded by the attribute
        'TXTDSC'. A short explanation may be given by the use of the attribute
        'INFORM'.
      </S100FC:remarks>
      <S100FC:alias>RESTRN</S100FC:alias>
      <S100FC:valueType>enumeration</S100FC:valueType>
      <S100FC:listedValues>
        <S100FC:listedValue>
          <S100FC:label>anchoring prohibited</S100FC:label>
          <S100FC:definition>
            an area within which anchoring is not
            permitted.
          </S100FC:definition>
          <S100FC:code>1</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>anchoring restricted</S100FC:label>
          <S100FC:definition>
            a specified area designated by appropriate authority, within
            which anchoring is restricted in accordance with certain specified
            conditions.
          </S100FC:definition>
          <S100FC:code>2</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>fishing prohibited</S100FC:label>
          <S100FC:definition>
            an area within which fishing is not
            permitted.
          </S100FC:definition>
          <S100FC:code>3</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>fishing restricted</S100FC:label>
          <S100FC:definition>
            a specified area designated by appropriate authority, within
            which fishing is restricted in accordance with certain specified
            conditions.
          </S100FC:definition>
          <S100FC:code>4</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>trawling prohibited</S100FC:label>
          <S100FC:definition>
            an area within which trawling is not
            permitted.
          </S100FC:definition>
          <S100FC:code>5</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>trawling restricted</S100FC:label>
          <S100FC:definition>
            a specified area designated by appropriate authority, within
            which trawling is restricted in accordance with certain specified
            conditions.
          </S100FC:definition>
          <S100FC:code>6</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>entry prohibited</S100FC:label>
          <S100FC:definition>
            an area within which navigation and/or anchoring is
            prohibited.
          </S100FC:definition>
          <S100FC:code>7</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>entry restricted</S100FC:label>
          <S100FC:definition>
            a specified area designated by appropriate authority, within
            which navigation is restricted in accordance with certain specified
            conditions.
          </S100FC:definition>
          <S100FC:code>8</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>dredging prohibited</S100FC:label>
          <S100FC:definition>
            an area within which dredging is not
            permitted.
          </S100FC:definition>
          <S100FC:code>9</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>dredging restricted</S100FC:label>
          <S100FC:definition>
            a specified area designated by appropriate authority, within
            which dredging is restricted in accordance with certain specified
            conditions.
          </S100FC:definition>
          <S100FC:code>10</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>diving prohibited</S100FC:label>
          <S100FC:definition>
            an area within which diving is not
            permitted.
          </S100FC:definition>
          <S100FC:code>11</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>diving restricted</S100FC:label>
          <S100FC:definition>
            a specified area designated by appropriate authority, within
            which diving is restricted in accordance with certain specified
            conditions.
          </S100FC:definition>
          <S100FC:code>12</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>no wake</S100FC:label>
          <S100FC:definition>
            mariners must adjust the speed of their vessels to reduce the
            wave or wash which may cause erosion or disturb moored
            vessels.
          </S100FC:definition>
          <S100FC:code>13</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>area to be avoided</S100FC:label>
          <S100FC:definition>
            an IMO designated area to be avoided, defined as a routeing
            measure.
          </S100FC:definition>
          <S100FC:code>14</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>construction prohibited</S100FC:label>
          <S100FC:definition>
            the erection of permanent or temporary fixed structures or
            artificial islands is prohibited.
          </S100FC:definition>
          <S100FC:code>15</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>discharging prohibited</S100FC:label>
          <S100FC:definition>
            an area within which discharging or dumping is
            prohibited
          </S100FC:definition>
          <S100FC:code>16</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>discharging restricted</S100FC:label>
          <S100FC:definition>
            a specified area designated by an appropriate authority,
            within which discharging or dumping is restricted in accordance with
            specified conditions.
          </S100FC:definition>
          <S100FC:code>17</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>
            industrial or mineral exploration/development
            prohibited
          </S100FC:label>
          <S100FC:definition>
            an area within which industrial or mineral exploration and
            development are prohibited.
          </S100FC:definition>
          <S100FC:code>18</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>
            industrial or mineral exploration/development
            restricted
          </S100FC:label>
          <S100FC:definition>
            a specified area designated by an appropriate authority,
            within which industrial or mineral exploration and development is restricted
            in accordance with certain specified conditions.
          </S100FC:definition>
          <S100FC:code>19</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>drilling prohibited</S100FC:label>
          <S100FC:definition>
            an area within which excavating a hole on the sea-bottom with
            a drill is prohibited.
          </S100FC:definition>
          <S100FC:code>20</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>drilling restricted</S100FC:label>
          <S100FC:definition>
            a specified area designated by an appropriate authority,
            within which excavating a hole on the sea-bottom with a drill is restricted
            in accordance with certain specified conditions.
          </S100FC:definition>
          <S100FC:code>21</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>removal of historical artifacts prohibited</S100FC:label>
          <S100FC:definition>
            an area within which the removal of historical artifacts is
            prohibited.
          </S100FC:definition>
          <S100FC:code>22</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>cargo transhipment (lightering) prohibited</S100FC:label>
          <S100FC:definition>
            an area in which cargo transhipment (lightering) is
            prohibited.
          </S100FC:definition>
          <S100FC:code>23</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>dragging prohibited</S100FC:label>
          <S100FC:definition>
            an area in which the dragging of anything along the bottom,
            e.g. bottom trawling, is prohibited.
          </S100FC:definition>
          <S100FC:code>24</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>stopping prohibited</S100FC:label>
          <S100FC:definition>
            an area in which a vessel is prohibited from
            stopping.
          </S100FC:definition>
          <S100FC:code>25</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>landing prohibited</S100FC:label>
          <S100FC:definition>an area in which landing is prohibited.</S100FC:definition>
          <S100FC:code>26</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>speed restricted</S100FC:label>
          <S100FC:definition>an area within which speed is restricted.</S100FC:definition>
          <S100FC:code>27</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>overtaking prohibited</S100FC:label>
          <S100FC:definition>
            a specified area designated by appropriate authority, within
            which overtaking is generally prohibited
          </S100FC:definition>
          <S100FC:code>28</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>overtaking of convoys by convoys prohibited</S100FC:label>
          <S100FC:definition>
            a specified area designated by appropriate authority, within
            which overtaking between convoys prohibited
          </S100FC:definition>
          <S100FC:code>29</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>passing or overtaking prohibited</S100FC:label>
          <S100FC:definition>
            a specified area designated by appropriate authority, within
            which passing or overtaking is generally prohibited
          </S100FC:definition>
          <S100FC:code>30</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>berthing prohibited</S100FC:label>
          <S100FC:definition>
            a specified area designated by appropriate authority, within
            which vessels, assemblies of floating material or floating establishments
            may not berth.
          </S100FC:definition>
          <S100FC:code>31</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>berthing restricted</S100FC:label>
          <S100FC:definition>
            a specified area designated by appropriate authority, within
            which berthing is restricted
          </S100FC:definition>
          <S100FC:code>32</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>making fast prohibited</S100FC:label>
          <S100FC:definition>
            a specified area designated by appropriate authority, within
            which vessels, assemblies of floating material or floating establishments
            may not make fast to the bank.
          </S100FC:definition>
          <S100FC:code>33</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>making fast restricted</S100FC:label>
          <S100FC:definition>
            a specified area designated by appropriate authority, within
            which making fast to the bank is restricted
          </S100FC:definition>
          <S100FC:code>34</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>turning prohibited</S100FC:label>
          <S100FC:definition>
            a specified area designated by appropriate authority, within
            which all turning is generally prohibited
          </S100FC:definition>
          <S100FC:code>35</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>restricted fairway depth</S100FC:label>
          <S100FC:definition>
            an area within which the fairway depth is
            restricted.
          </S100FC:definition>
          <S100FC:code>36</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>restricted fairway width</S100FC:label>
          <S100FC:definition>
            an area within which the fairway width is
            restricted.
          </S100FC:definition>
          <S100FC:code>37</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>use of spuds prohibited</S100FC:label>
          <S100FC:definition>
            The use of anchoring spuds (telescopic piles) is
            prohibited
          </S100FC:definition>
          <S100FC:code>38</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>swimming prohibited</S100FC:label>
          <S100FC:definition>An area in which swimming is prohibited</S100FC:definition>
          <S100FC:code>39</S100FC:code>
        </S100FC:listedValue>
      </S100FC:listedValues>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Value Of Sounding</S100FC:name>
      <S100FC:definition>Value Of Sounding</S100FC:definition>
      <S100FC:code>valueOfSounding</S100FC:code>
      <S100FC:valueType>real</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Vertical Uncertainty</S100FC:name>
      <S100FC:definition>Vertical Uncertainty</S100FC:definition>
      <S100FC:code>verticalUncertainty</S100FC:code>
      <S100FC:valueType>text</S100FC:valueType>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Water Level Effect</S100FC:name>
      <S100FC:definition>Water Level Effect</S100FC:definition>
      <S100FC:code>waterLevelEffect</S100FC:code>
      <S100FC:valueType>enumeration</S100FC:valueType>
      <S100FC:listedValues>
        <S100FC:listedValue>
          <S100FC:label>partly submerged at high water</S100FC:label>
          <S100FC:definition>partly submerged at high water</S100FC:definition>
          <S100FC:code>1</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>always dry</S100FC:label>
          <S100FC:definition>always dry</S100FC:definition>
          <S100FC:code>2</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>always under water/submerged</S100FC:label>
          <S100FC:definition>always under water/submerged</S100FC:definition>
          <S100FC:code>3</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>covers and unconvers</S100FC:label>
          <S100FC:definition>covers and unconvers</S100FC:definition>
          <S100FC:code>4</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>awash</S100FC:label>
          <S100FC:definition>awash</S100FC:definition>
          <S100FC:code>5</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>floating</S100FC:label>
          <S100FC:definition>floating</S100FC:definition>
          <S100FC:code>7</S100FC:code>
        </S100FC:listedValue>
      </S100FC:listedValues>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Category of temporal variation</S100FC:name>
      <S100FC:definition>
        An assessment of the likelihood of change over
        time.
      </S100FC:definition>
      <S100FC:code>categoryOfTemporalVariation</S100FC:code>
      <S100FC:valueType>enumeration</S100FC:valueType>
      <S100FC:listedValues>
        <S100FC:listedValue>
          <S100FC:label>Extreme Event</S100FC:label>
          <S100FC:definition>
            Indication of the possible impact of a significant event (for
            example hurricane, earthquake, volcanic eruption, landslide, etc), which is
            considered likely to have changed the seafloor or landscape
            significantly.
          </S100FC:definition>
          <S100FC:code>1</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>Likely to Change</S100FC:label>
          <S100FC:definition>
            Continuous or frequent change to non-bathymetric features
            (for example river siltation, glacier creep/recession, sand dunes, buoys,
            marine farms, etc.).
          </S100FC:definition>
          <S100FC:code>4</S100FC:code>
        </S100FC:listedValue>
        <S100FC:listedValue>
          <S100FC:label>Unlikely to Change</S100FC:label>
          <S100FC:definition>
            Significant change to the seafloor is not
            expected.
          </S100FC:definition>
          <S100FC:code>5</S100FC:code>
        </S100FC:listedValue>
      </S100FC:listedValues>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Maximum display scale</S100FC:name>
      <S100FC:definition>The largest intended viewing scale for the data.</S100FC:definition>
      <S100FC:code>maximumDisplayScale</S100FC:code>
      <S100FC:valueType>integer</S100FC:valueType>
      <S100FC:constraints>
        <S100FD:range>
          <S100Base:lowerBound>1</S100Base:lowerBound>
          <S100Base:closure>geSemiInterval</S100Base:closure>
        </S100FD:range>
      </S100FC:constraints>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Minimum display scale</S100FC:name>
      <S100FC:definition>The smallest intended viewing scale for the data.</S100FC:definition>
      <S100FC:code>minimumDisplayScale</S100FC:code>
      <S100FC:valueType>integer</S100FC:valueType>
      <S100FC:constraints>
        <S100FD:range>
          <S100Base:lowerBound>1</S100Base:lowerBound>
          <S100Base:closure>geSemiInterval</S100Base:closure>
        </S100FD:range>
      </S100FC:constraints>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Orientation uncertainty</S100FC:name>
      <S100FC:definition>The best estimate of the accuracy of a bearing.</S100FC:definition>
      <S100FC:code>orientationUncertainty</S100FC:code>
      <S100FC:valueType>real</S100FC:valueType>
      <S100FC:uom>
        <S100Base:name>degrees</S100Base:name>
        <S100Base:definition>degrees of arc</S100Base:definition>
        <S100Base:symbol>°</S100Base:symbol>
      </S100FC:uom>
      <S100FC:quantitySpecification>planeAngle</S100FC:quantitySpecification>
      <S100FC:constraints>
        <S100FD:range>
          <S100Base:lowerBound>0.000</S100Base:lowerBound>
          <S100Base:upperBound>360.000</S100Base:upperBound>
          <S100Base:closure>closedInterval</S100Base:closure>
        </S100FD:range>
        <S100FD:precision>3</S100FD:precision>
      </S100FC:constraints>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Horizontal distance uncertainty</S100FC:name>
      <S100FC:definition>
        The best estimate of the horizontal accuracy of horizontal clearances
        and distances.
      </S100FC:definition>
      <S100FC:code>horizontalDistanceUncertainty</S100FC:code>
      <S100FC:remarks>
        the error is assumed to be positive and negative. The plus/minus
        character must not be encoded.
      </S100FC:remarks>
      <S100FC:alias>HORACC</S100FC:alias>
      <S100FC:valueType>real</S100FC:valueType>
      <S100FC:uom>
        <S100Base:name>metres</S100Base:name>
        <S100Base:definition>SI Metres</S100Base:definition>
        <S100Base:symbol>m</S100Base:symbol>
      </S100FC:uom>
      <S100FC:quantitySpecification>length</S100FC:quantitySpecification>
      <S100FC:constraints>
        <S100FD:range>
          <S100Base:lowerBound>0</S100Base:lowerBound>
          <S100Base:closure>geSemiInterval</S100Base:closure>
        </S100FD:range>
        <S100FD:precision>1</S100FD:precision>
      </S100FC:constraints>
    </S100FC:S100_FC_SimpleAttribute>
    <S100FC:S100_FC_SimpleAttribute>
      <S100FC:name>Uncertainty Fixed</S100FC:name>
      <S100FC:definition>
        The best estimate of the fixed horizontal or vertical accuracy
        component for positions, depths, heights, vertical distances and vertical
        clearances.
      </S100FC:definition>
      <S100FC:code>uncertaintyFixed</S100FC:code>
      <S100FC:alias>POSACC; SOUACC; VERACC</S100FC:alias>
      <S100FC:valueType>real</S100FC:valueType>
      <S100FC:uom>
        <S100Base:name>metre</S100Base:name>
        <S100Base:definition>SI metre</S100Base:definition>
        <S100Base:symbol>m</S100Base:symbol>
      </S100FC:uom>
      <S100FC:quantitySpecification>length</S100FC:quantitySpecification>
      <S100FC:constraints>
        <S100FD:range>
          <S100Base:lowerBound>0.0</S100Base:lowerBound>
          <S100Base:closure>leSemiInterval</S100Base:closure>
        </S100FD:range>
        <S100FD:precision>1</S100FD:precision>
      </S100FC:constraints>
    </S100FC:S100_FC_SimpleAttribute>
  </S100FC:S100_FC_SimpleAttributes>




  <S100FC:S100_FC_ComplexAttributes>
    <S100FC:S100_FC_ComplexAttribute>
      <S100FC:name>Feature name</S100FC:name>
      <S100FC:definition>The complex attribute provides the name of an entity, defines the national language of the name, and provides the option to display the name at various system display settings.</S100FC:definition>
      <S100FC:code>featureName</S100FC:code>
      <S100FC:subAttributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="displayName"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="language"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>1</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="name"/>
      </S100FC:subAttributeBinding>
    </S100FC:S100_FC_ComplexAttribute>
    <S100FC:S100_FC_ComplexAttribute>
      <S100FC:name>Fixed date range</S100FC:name>
      <S100FC:definition>The complex attribute describes single fixed period, as the date range between its sub-attributes.</S100FC:definition>
      <S100FC:code>fixedDateRange</S100FC:code>
      <S100FC:remarks>the sub-attributes date start and date end must be encoded using 4 digits for the calendar year (YYYY) and, optionally, 2 digits for the month (MM) (e.g. April = 04) and 2 digits for the day (DD). When no specific month and/or day is required/known, the values are replaced with dashes (-).</S100FC:remarks>
      <S100FC:subAttributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="dateEnd"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="dateStart"/>
      </S100FC:subAttributeBinding>
    </S100FC:S100_FC_ComplexAttribute>
    <S100FC:S100_FC_ComplexAttribute>
      <S100FC:name>Periodic date range</S100FC:name>
      <S100FC:definition>The complex attribute describes the active period for a seasonal feature (e.g. a buoy), as the dates between its sub-attributes</S100FC:definition>
      <S100FC:code>periodicDateRange</S100FC:code>
      <S100FC:remarks>The sub-attributes date start and date end should be encoded using 4 digits for the calendar year (YYYY), 2 digits for the month (MM) (for example April = 04) and 2 digits for the day (DD). When no specific year is required (that is, the feature is removed at the same time each year) the following two cases may be considered: - same day each year: ----MMDD - same month each year: ----MM-- This conforms to ISO 8601:2004.</S100FC:remarks>
      <S100FC:subAttributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>1</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="dateEnd"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>1</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="dateStart"/>
      </S100FC:subAttributeBinding>
    </S100FC:S100_FC_ComplexAttribute>
    <S100FC:S100_FC_ComplexAttribute>
      <S100FC:name>Source indication</S100FC:name>
      <S100FC:definition>Information about the source document, publication, or reference from which object data or textual material included or referenced in a dataset are derived</S100FC:definition>
      <S100FC:code>sourceIndication</S100FC:code>
      <S100FC:alias>SORIND</S100FC:alias>
      <S100FC:subAttributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:permittedValues>
          <S100FC:value>1</S100FC:value>
          <S100FC:value>2</S100FC:value>
          <S100FC:value>3</S100FC:value>
          <S100FC:value>4</S100FC:value>
          <S100FC:value>5</S100FC:value>
          <S100FC:value>6</S100FC:value>
          <S100FC:value>7</S100FC:value>
          <S100FC:value>8</S100FC:value>
          <S100FC:value>9</S100FC:value>
          <S100FC:value>10</S100FC:value>
          <S100FC:value>11</S100FC:value>
          <S100FC:value>12</S100FC:value>
          <S100FC:value>13</S100FC:value>
          <S100FC:value>14</S100FC:value>
          <S100FC:value>15</S100FC:value>
        </S100FC:permittedValues>
        <S100FC:attribute ref="categoryOfAuthority"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="country"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding sequential="true">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:attribute ref="engName"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding sequential="true">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:attribute ref="korName"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="reportedDate"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="source"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:permittedValues>
          <S100FC:value>1</S100FC:value>
          <S100FC:value>2</S100FC:value>
          <S100FC:value>7</S100FC:value>
          <S100FC:value>8</S100FC:value>
          <S100FC:value>9</S100FC:value>
          <S100FC:value>10</S100FC:value>
          <S100FC:value>11</S100FC:value>
          <S100FC:value>12</S100FC:value>
          <S100FC:value>13</S100FC:value>
          <S100FC:value>14</S100FC:value>
        </S100FC:permittedValues>
        <S100FC:attribute ref="sourceType"/>
      </S100FC:subAttributeBinding>
    </S100FC:S100_FC_ComplexAttribute>
    <S100FC:S100_FC_ComplexAttribute>
      <S100FC:name>Text content</S100FC:name>
      <S100FC:definition>Textual material, or a pointer to a resource providing textual material. May be accompanied by basic information about its source and relationship to the source.</S100FC:definition>
      <S100FC:code>textContent</S100FC:code>
      <S100FC:remarks>
        textContent is intended to allow text passages from other publications to be included in, or referenced by, instances of feature or information types.
        Exactly one of sub-attributes onlineResource or information must be completed in one instance of textContent.
        Product specifications may restrict the use or content  of onlineResource for security. For example, a product specification may forbid populating onlineResource.
        Product specification authors must consider whether applications using the data product may be prevented from accessing off-system resources by security policies.
      </S100FC:remarks>
      <S100FC:subAttributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:permittedValues>
          <S100FC:value>1</S100FC:value>
          <S100FC:value>2</S100FC:value>
          <S100FC:value>3</S100FC:value>
        </S100FC:permittedValues>
        <S100FC:attribute ref="categoryOfText"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:attribute ref="information"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper>1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="onlineResource"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper>1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="sourceIndication"/>
      </S100FC:subAttributeBinding>
    </S100FC:S100_FC_ComplexAttribute>
    <S100FC:S100_FC_ComplexAttribute>
      <S100FC:name>Information</S100FC:name>
      <S100FC:definition>The complex attribute provides additional textual information that cannot be provided using other allowable attributes for the feature, and defines the language of the text string.</S100FC:definition>
      <S100FC:code>information</S100FC:code>
      <S100FC:remarks>this complex attribute should be used, for example, to hold the information that is shown on paper charts by cautionary and explanatory notes.</S100FC:remarks>
      <S100FC:subAttributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="fileLocator"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="fileReference"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="headline"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="language"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="text"/>
      </S100FC:subAttributeBinding>
    </S100FC:S100_FC_ComplexAttribute>
    <S100FC:S100_FC_ComplexAttribute>
      <S100FC:name>Online resource</S100FC:name>
      <S100FC:definition>Information about online sources from which a resource or data can be obtained.</S100FC:definition>
      <S100FC:code>onlineResource</S100FC:code>
      <S100FC:remarks>The complex attribute describes the access to online resources according to ISO 19115.</S100FC:remarks>
      <S100FC:subAttributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>1</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="linkage"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="protocol"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="applicationProfile"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="nameOfResource"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="onlineDescription"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:permittedValues>
          <S100FC:value>1</S100FC:value>
          <S100FC:value>2</S100FC:value>
          <S100FC:value>3</S100FC:value>
          <S100FC:value>4</S100FC:value>
          <S100FC:value>5</S100FC:value>
          <S100FC:value>6</S100FC:value>
          <S100FC:value>7</S100FC:value>
          <S100FC:value>8</S100FC:value>
          <S100FC:value>9</S100FC:value>
          <S100FC:value>10</S100FC:value>
          <S100FC:value>11</S100FC:value>
        </S100FC:permittedValues>
        <S100FC:attribute ref="onlineFunction"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="protocolRequest"/>
      </S100FC:subAttributeBinding>
    </S100FC:S100_FC_ComplexAttribute>
    <S100FC:S100_FC_ComplexAttribute>
      <S100FC:name>Contact address</S100FC:name>
      <S100FC:definition>Direction or superscription of a letter, package, etc., specifying the name of the place to which it is directed, and optionally a contact person or organisation who should receive it. (Oxford English Dictionary, 2nd Ed., adapted).</S100FC:definition>
      <S100FC:code>contactAddress</S100FC:code>
      <S100FC:subAttributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:attribute ref="deliveryPoint"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper>1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="cityName"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper>1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="administrativeDivision"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper>1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="country"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper>1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="postalCode"/>
      </S100FC:subAttributeBinding>
    </S100FC:S100_FC_ComplexAttribute>
    <S100FC:S100_FC_ComplexAttribute>
      <S100FC:name>Horizontal position uncertainty</S100FC:name>
      <S100FC:definition>The best estimate of the accuracy of a position.</S100FC:definition>
      <S100FC:code>horizontalPositionUncertainty</S100FC:code>
      <S100FC:remarks>
        The expected input is the maximum of the two-dimensional error. The
        error is assumed to be positive and negative.
      </S100FC:remarks>
      <S100FC:subAttributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>1</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="uncertaintyFixed"/>
      </S100FC:subAttributeBinding>
      <!--<S100FC:subAttributeBinding sequential="false"> <S100FC:multiplicity> <S100Base:lower>0</S100Base:lower> <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper> </S100FC:multiplicity> <S100FC:attribute ref="uncertaintyVariableFactor"/> </S100FC:subAttributeBinding>-->
    </S100FC:S100_FC_ComplexAttribute>
    <S100FC:S100_FC_ComplexAttribute>
      <S100FC:name>Survey date range</S100FC:name>
      <S100FC:definition>
        The complex attribute describes the period of the hydrographic
        survey, as the time between its sub-attributes.
      </S100FC:definition>
      <S100FC:code>surveyDateRange</S100FC:code>
      <S100FC:subAttributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>1</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="dateEnd"/>
      </S100FC:subAttributeBinding>
      <S100FC:subAttributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="dateStart"/>
      </S100FC:subAttributeBinding>
    </S100FC:S100_FC_ComplexAttribute>

  </S100FC:S100_FC_ComplexAttributes>

  <S100FC:S100_FC_Roles>
    <S100FC:S100_FC_Role>
      <S100FC:name>Contact details (reference)</S100FC:name>
      <S100FC:definition>A pointer to an Contact Details object</S100FC:definition>
      <S100FC:code>theContactDetails</S100FC:code>
    </S100FC:S100_FC_Role>
    <S100FC:S100_FC_Role>
      <S100FC:name>Authority (reference)</S100FC:name>
      <S100FC:definition>A pointer to an Authority object</S100FC:definition>
      <S100FC:code>theAuthority</S100FC:code>
    </S100FC:S100_FC_Role>
    <S100FC:S100_FC_Role>
      <S100FC:name>registered</S100FC:name>
      <S100FC:definition>registered</S100FC:definition>
      <S100FC:code>registered</S100FC:code>
    </S100FC:S100_FC_Role>
    <S100FC:S100_FC_Role>
      <S100FC:name>Registration Authority</S100FC:name>
      <S100FC:definition>Registration Authority</S100FC:definition>
      <S100FC:code>registrationAuthority</S100FC:code>
    </S100FC:S100_FC_Role>
  </S100FC:S100_FC_Roles>

  <S100FC:S100_FC_InformationAssociations>
    <S100FC:S100_FC_InformationAssociation>
      <S100FC:name>Authority contact</S100FC:name>
      <S100FC:definition>Contact information for an authority</S100FC:definition>
      <S100FC:code>authorityContact</S100FC:code>
      <S100FC:role ref="theAuthority"/>
      <S100FC:role ref="theContactDetails"/>
    </S100FC:S100_FC_InformationAssociation>
    <S100FC:S100_FC_InformationAssociation>
      <S100FC:name>Competent Authority</S100FC:name>
      <S100FC:definition>competentAuthority</S100FC:definition>
      <S100FC:code>competentAuthority</S100FC:code>
      <S100FC:role ref="registered"/>
      <S100FC:role ref="registrationAuthority"/>
    </S100FC:S100_FC_InformationAssociation>
  </S100FC:S100_FC_InformationAssociations>

  <S100FC:S100_FC_InformationTypes>
    <S100FC:S100_FC_InformationType isAbstract="true">
      <S100FC:name>InformationType</S100FC:name>
      <S100FC:definition>Generalized information type which carries all the common attributes</S100FC:definition>
      <S100FC:code>InformationType</S100FC:code>
      <S100FC:attributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="fixedDateRange"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:attribute ref="periodicDateRange"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:attribute ref="featureName"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:attribute ref="sourceIndication"/>
      </S100FC:attributeBinding>
    </S100FC:S100_FC_InformationType>
    <S100FC:S100_FC_InformationType isAbstract="false">
      <S100FC:name>Contact details</S100FC:name>
      <S100FC:definition>information on how to reach a person or organisation by postal, internet, telephone, telex and radio systems</S100FC:definition>
      <S100FC:code>ContactDetails</S100FC:code>

      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:attribute ref="communicationChannel"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:attribute ref="contactAddress"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="contactInstructions"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:attribute ref="information"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:attribute ref="onlineResource"/>
      </S100FC:attributeBinding>
      <S100FC:informationBinding roleType="association">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:association ref="authorityContact"/>
        <S100FC:role ref="theAuthority"/>
        <S100FC:informationType ref="Authority"/>
      </S100FC:informationBinding>
      <S100FC:superType>InformationType</S100FC:superType>
    </S100FC:S100_FC_InformationType>
    <S100FC:S100_FC_InformationType isAbstract="false">
      <S100FC:name>Authority</S100FC:name>
      <S100FC:definition>A person or organisation having political or administrative power and control.</S100FC:definition>
      <S100FC:code>Authority</S100FC:code>

      <S100FC:attributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>1</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:permittedValues>
          <S100FC:value>1</S100FC:value>
          <S100FC:value>2</S100FC:value>
          <S100FC:value>3</S100FC:value>
          <S100FC:value>4</S100FC:value>
          <S100FC:value>5</S100FC:value>
          <S100FC:value>6</S100FC:value>
          <S100FC:value>7</S100FC:value>
          <S100FC:value>8</S100FC:value>
          <S100FC:value>9</S100FC:value>
          <S100FC:value>10</S100FC:value>
          <S100FC:value>11</S100FC:value>
          <S100FC:value>12</S100FC:value>
          <S100FC:value>13</S100FC:value>
          <S100FC:value>14</S100FC:value>
          <S100FC:value>15</S100FC:value>
        </S100FC:permittedValues>
        <S100FC:attribute ref="categoryOfAuthority"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="textContent"/>
      </S100FC:attributeBinding>
      <S100FC:informationBinding roleType="association">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:association ref="authorityContact"/>
        <S100FC:role ref="theContactDetails"/>
        <S100FC:informationType ref="ContactDetails"/>
      </S100FC:informationBinding>
      <S100FC:superType>InformationType</S100FC:superType>
    </S100FC:S100_FC_InformationType>
  </S100FC:S100_FC_InformationTypes>




  <S100FC:S100_FC_FeatureTypes>
    <S100FC:S100_FC_FeatureType isAbstract="true">
      <S100FC:name>FeatureType</S100FC:name>
      <S100FC:definition>Generalized feature type which carries all the common attributes</S100FC:definition>
      <S100FC:code>FeatureType</S100FC:code>

      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="contactAddress"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:attribute ref="featureName"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="fisheryLocation"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:permittedValues>
          <S100FC:value>1</S100FC:value>
          <S100FC:value>2</S100FC:value>
          <S100FC:value>3</S100FC:value>
        </S100FC:permittedValues>
        <S100FC:attribute ref="fisheryRight"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="fishingMethod"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="fixedDateRange"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="licenseNumber"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:attribute ref="periodicDateRange"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="scaleMinimum"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="sourceIndication"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:permittedValues>
          <!--수정해야되는데-->
          <S100FC:value>1</S100FC:value>
          <S100FC:value>2</S100FC:value>
          <S100FC:value>3</S100FC:value>
          <S100FC:value>4</S100FC:value>
          <S100FC:value>5</S100FC:value>
          <S100FC:value>6</S100FC:value>
          <S100FC:value>7</S100FC:value>
          <S100FC:value>9</S100FC:value>
          <S100FC:value>18</S100FC:value>
          <S100FC:value>28</S100FC:value>
        </S100FC:permittedValues>
        <S100FC:attribute ref="status"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:attribute ref="textContent"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="typeOfCulture"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="verticalLength"/>
      </S100FC:attributeBinding>
      <S100FC:informationBinding roleType="association">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:association ref="competentAuthority"/>
        <S100FC:role ref="registrationAuthority"/>
        <S100FC:informationType ref="Authority"/>
      </S100FC:informationBinding>
      <S100FC:featureUseType>geographic</S100FC:featureUseType>
      <S100FC:permittedPrimitives>noGeometry</S100FC:permittedPrimitives>
    </S100FC:S100_FC_FeatureType>
    <S100FC:S100_FC_FeatureType isAbstract="false">
      <S100FC:name>Fishing Facility</S100FC:name>
      <S100FC:definition>Fishing Facility</S100FC:definition>
      <S100FC:code>FishingFacility</S100FC:code>

      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:permittedValues>
          <S100FC:value>1</S100FC:value>
          <S100FC:value>2</S100FC:value>
          <S100FC:value>3</S100FC:value>
          <S100FC:value>4</S100FC:value>
        </S100FC:permittedValues>
        <S100FC:attribute ref="categoryOfFishingFacility"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:permittedValues>
          <S100FC:value>1</S100FC:value>
          <S100FC:value>2</S100FC:value>
          <S100FC:value>3</S100FC:value>
        </S100FC:permittedValues>
        <S100FC:attribute ref="condition"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="reportedDate"/>
      </S100FC:attributeBinding>


      <S100FC:superType>FeatureType</S100FC:superType>
      <S100FC:featureUseType>geographic</S100FC:featureUseType>
      <S100FC:permittedPrimitives>curve</S100FC:permittedPrimitives>
      <S100FC:permittedPrimitives>surface</S100FC:permittedPrimitives>
    </S100FC:S100_FC_FeatureType>
    <S100FC:S100_FC_FeatureType isAbstract="false">
      <S100FC:name>Marine Farm Culture</S100FC:name>
      <S100FC:definition>Marine Farm Culture</S100FC:definition>
      <S100FC:code>MarineFarmCulture</S100FC:code>

      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:permittedValues>
          <S100FC:value>1</S100FC:value>
          <S100FC:value>2</S100FC:value>
          <S100FC:value>3</S100FC:value>
          <S100FC:value>4</S100FC:value>
          <S100FC:value>5</S100FC:value>
        </S100FC:permittedValues>
        <S100FC:attribute ref="categoryOfMarineFarmCulture"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:permittedValues>
          <S100FC:value>1</S100FC:value>
          <S100FC:value>2</S100FC:value>
        </S100FC:permittedValues>
        <S100FC:attribute ref="expositionOfSounding"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:permittedValues>
          <S100FC:value>1</S100FC:value>
          <S100FC:value>2</S100FC:value>
          <S100FC:value>3</S100FC:value>
          <S100FC:value>4</S100FC:value>
          <S100FC:value>6</S100FC:value>
          <S100FC:value>7</S100FC:value>
          <S100FC:value>8</S100FC:value>
          <S100FC:value>9</S100FC:value>
        </S100FC:permittedValues>
        <S100FC:attribute ref="qualityOfVerticalMeasurement"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:permittedValues>
          <S100FC:value>1</S100FC:value>
          <S100FC:value>2</S100FC:value>
          <S100FC:value>3</S100FC:value>
          <S100FC:value>4</S100FC:value>
          <S100FC:value>5</S100FC:value>
          <S100FC:value>6</S100FC:value>
          <S100FC:value>7</S100FC:value>
          <S100FC:value>8</S100FC:value>
          <S100FC:value>9</S100FC:value>
          <S100FC:value>10</S100FC:value>
          <S100FC:value>11</S100FC:value>
          <S100FC:value>12</S100FC:value>
          <S100FC:value>13</S100FC:value>
          <S100FC:value>14</S100FC:value>
          <S100FC:value>15</S100FC:value>
          <S100FC:value>16</S100FC:value>
          <S100FC:value>17</S100FC:value>
          <S100FC:value>18</S100FC:value>
          <S100FC:value>19</S100FC:value>
          <S100FC:value>20</S100FC:value>
          <S100FC:value>21</S100FC:value>
          <S100FC:value>22</S100FC:value>
          <S100FC:value>23</S100FC:value>
          <S100FC:value>24</S100FC:value>
          <S100FC:value>25</S100FC:value>
          <S100FC:value>26</S100FC:value>
          <S100FC:value>27</S100FC:value>
          <S100FC:value>39</S100FC:value>
        </S100FC:permittedValues>
        <S100FC:attribute ref="restriction"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>1</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="valueOfSounding"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding>
        <S100FC:multiplicity>
          <S100Base:lower>1</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="verticalUncertainty"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:permittedValues>
          <S100FC:value>1</S100FC:value>
          <S100FC:value>2</S100FC:value>
          <S100FC:value>3</S100FC:value>
          <S100FC:value>4</S100FC:value>
          <S100FC:value>5</S100FC:value>
          <S100FC:value>7</S100FC:value>
        </S100FC:permittedValues>
        <S100FC:attribute ref="waterLevelEffect"/>
      </S100FC:attributeBinding>

      <S100FC:superType>FeatureType</S100FC:superType>
      <S100FC:featureUseType>geographic</S100FC:featureUseType>
      <S100FC:permittedPrimitives>curve</S100FC:permittedPrimitives>
      <S100FC:permittedPrimitives>surface</S100FC:permittedPrimitives>
    </S100FC:S100_FC_FeatureType>

    <S100FC:S100_FC_FeatureType isAbstract="true">
      <S100FC:name>Data quality</S100FC:name>
      <S100FC:definition>Abstract feature type for data quality meta-features.</S100FC:definition>
      <S100FC:code>DataQuality</S100FC:code>

      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="true" infinite="true"/>
        </S100FC:multiplicity>
        <S100FC:attribute ref="information"/>
      </S100FC:attributeBinding>
      <S100FC:featureUseType>meta</S100FC:featureUseType>
      <S100FC:permittedPrimitives>surface</S100FC:permittedPrimitives>
    </S100FC:S100_FC_FeatureType>
    <S100FC:S100_FC_FeatureType isAbstract="true">
      <S100FC:name>Quality of temporal variation</S100FC:name>
      <S100FC:definition>Abstract type for meta-feature which can describe temporal variation.</S100FC:definition>
      <S100FC:code>QualityOfTemporalVariation</S100FC:code>

      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:permittedValues>
          <S100FC:value>1</S100FC:value>
          <S100FC:value>4</S100FC:value>
          <S100FC:value>5</S100FC:value>
        </S100FC:permittedValues>
        <S100FC:attribute ref="categoryOfTemporalVariation"/>
      </S100FC:attributeBinding>
      <S100FC:superType>DataQuality</S100FC:superType>
      <S100FC:featureUseType>meta</S100FC:featureUseType>
      <S100FC:permittedPrimitives>surface</S100FC:permittedPrimitives>
    </S100FC:S100_FC_FeatureType>
    <!-- Meta features -->
    <S100FC:S100_FC_FeatureType isAbstract="false">
      <S100FC:name>Data coverage</S100FC:name>
      <S100FC:definition>A geographical area that describes the coverage and extent of spatial types.</S100FC:definition>
      <S100FC:code>DataCoverage</S100FC:code>

      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>1</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="maximumDisplayScale"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>1</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="minimumDisplayScale"/>
      </S100FC:attributeBinding>
      <S100FC:featureUseType>meta</S100FC:featureUseType>
      <S100FC:permittedPrimitives>surface</S100FC:permittedPrimitives>
    </S100FC:S100_FC_FeatureType>
    <S100FC:S100_FC_FeatureType isAbstract="false">
      <S100FC:name>Quality of Non-Bathymetric Data</S100FC:name>
      <S100FC:definition>
        An area within which a uniform assessment of the quality of the
        non-bathymetric data exists
      </S100FC:definition>
      <S100FC:code>QualityOfNonBathymetricData</S100FC:code>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="orientationUncertainty"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="horizontalDistanceUncertainty"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="horizontalPositionUncertainty"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper xsi:nil="false" infinite="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="sourceIndication"/>
      </S100FC:attributeBinding>
      <S100FC:attributeBinding sequential="false">
        <S100FC:multiplicity>
          <S100Base:lower>0</S100Base:lower>
          <S100Base:upper infinite="false" xsi:nil="false">1</S100Base:upper>
        </S100FC:multiplicity>
        <S100FC:attribute ref="surveyDateRange"/>
      </S100FC:attributeBinding>
      <S100FC:superType>QualityOfTemporalVariation</S100FC:superType>
      <S100FC:featureUseType>meta</S100FC:featureUseType>
      <S100FC:permittedPrimitives>surface</S100FC:permittedPrimitives>
    </S100FC:S100_FC_FeatureType>
  </S100FC:S100_FC_FeatureTypes>
</S100FC:S100_FC_FeatureCatalogue>