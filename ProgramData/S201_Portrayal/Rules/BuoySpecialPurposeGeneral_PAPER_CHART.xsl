<?xml version="1.0" encoding="UTF-8"?>

<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
   <xsl:output method="xml" encoding="UTF-8" indent="yes"/>
   <xsl:template match="BuoySpecialPurposeGeneral[@primitive='Point']" priority="1">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>27010</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="BOYGEN03"/>
      </pointInstruction>
      <xsl:if test="featureName!= ''">
         <textInstruction>
            <featureReference>
               <xsl:value-of select="@id"/>
            </featureReference>
            <viewingGroup>21</viewingGroup>
            <displayPlane>OVERRADAR</displayPlane>
            <drawingPriority>24</drawingPriority>
            <textPoint horizontalAlignment="End">
               <element>
                  <text>
                     <xsl:apply-templates select="featureName" mode="text">
                        <xsl:with-param name="prefix">by </xsl:with-param>
                     </xsl:apply-templates>
                  </text>
                  <xsl:call-template name="textStyle">
                     <xsl:with-param name="style">default</xsl:with-param>
                  </xsl:call-template>
               </element>
               <offset>
                  <x>-3.51</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoySpecialPurposeGeneral[@primitive='Point' and buoyShape=1]" priority="2">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>27010</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="BOYCON01"/>
      </pointInstruction>
      <xsl:if test="featureName!= ''">
         <textInstruction>
            <featureReference>
               <xsl:value-of select="@id"/>
            </featureReference>
            <viewingGroup>21</viewingGroup>
            <displayPlane>OVERRADAR</displayPlane>
            <drawingPriority>24</drawingPriority>
            <textPoint horizontalAlignment="End">
               <element>
                  <text>
                     <xsl:apply-templates select="featureName" mode="text">
                        <xsl:with-param name="prefix">by </xsl:with-param>
                     </xsl:apply-templates>
                  </text>
                  <xsl:call-template name="textStyle">
                     <xsl:with-param name="style">default</xsl:with-param>
                  </xsl:call-template>
               </element>
               <offset>
                  <x>-3.51</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoySpecialPurposeGeneral[@primitive='Point' and buoyShape=2]" priority="2">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>27010</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="BOYCAN01"/>
      </pointInstruction>
      <xsl:if test="featureName!= ''">
         <textInstruction>
            <featureReference>
               <xsl:value-of select="@id"/>
            </featureReference>
            <viewingGroup>21</viewingGroup>
            <displayPlane>OVERRADAR</displayPlane>
            <drawingPriority>24</drawingPriority>
            <textPoint horizontalAlignment="End">
               <element>
                  <text>
                     <xsl:apply-templates select="featureName" mode="text">
                        <xsl:with-param name="prefix">by </xsl:with-param>
                     </xsl:apply-templates>
                  </text>
                  <xsl:call-template name="textStyle">
                     <xsl:with-param name="style">default</xsl:with-param>
                  </xsl:call-template>
               </element>
               <offset>
                  <x>-3.51</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoySpecialPurposeGeneral[@primitive='Point' and buoyShape=3]" priority="2">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>27010</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="구형 (황)"/>
      </pointInstruction>
      <xsl:if test="featureName!= ''">
         <textInstruction>
            <featureReference>
               <xsl:value-of select="@id"/>
            </featureReference>
            <viewingGroup>21</viewingGroup>
            <displayPlane>OVERRADAR</displayPlane>
            <drawingPriority>24</drawingPriority>
            <textPoint horizontalAlignment="End">
               <element>
                  <text>
                     <xsl:apply-templates select="featureName" mode="text">
                        <xsl:with-param name="prefix">by </xsl:with-param>
                     </xsl:apply-templates>
                  </text>
                  <xsl:call-template name="textStyle">
                     <xsl:with-param name="style">default</xsl:with-param>
                  </xsl:call-template>
               </element>
               <offset>
                  <x>-3.51</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoySpecialPurposeGeneral[@primitive='Point' and buoyShape=4]" priority="2">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>27010</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="특수표지(pillar)"/>
      </pointInstruction>
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>27010</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="분류기준선(Buoy)"/>
      </pointInstruction>
      <xsl:if test="featureName!= ''">
         <textInstruction>
            <featureReference>
               <xsl:value-of select="@id"/>
            </featureReference>
            <viewingGroup>21</viewingGroup>
            <displayPlane>OVERRADAR</displayPlane>
            <drawingPriority>24</drawingPriority>
            <textPoint horizontalAlignment="End">
               <element>
                  <text>
                     <xsl:apply-templates select="featureName" mode="text">
                        <xsl:with-param name="prefix">by </xsl:with-param>
                     </xsl:apply-templates>
                  </text>
                  <xsl:call-template name="textStyle">
                     <xsl:with-param name="style">default</xsl:with-param>
                  </xsl:call-template>
               </element>
               <offset>
                  <x>-3.51</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoySpecialPurposeGeneral[@primitive='Point' and buoyShape=5]" priority="3">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>27010</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="특수표지(spar)"/>
      </pointInstruction>
      <xsl:if test="featureName!= ''">
         <textInstruction>
            <featureReference>
               <xsl:value-of select="@id"/>
            </featureReference>
            <viewingGroup>21</viewingGroup>
            <displayPlane>OVERRADAR</displayPlane>
            <drawingPriority>24</drawingPriority>
            <textPoint horizontalAlignment="End">
               <element>
                  <text>
                     <xsl:apply-templates select="featureName" mode="text">
                        <xsl:with-param name="prefix">by </xsl:with-param>
                     </xsl:apply-templates>
                  </text>
                  <xsl:call-template name="textStyle">
                     <xsl:with-param name="style">default</xsl:with-param>
                  </xsl:call-template>
               </element>
               <offset>
                  <x>-3.51</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoySpecialPurposeGeneral[@primitive='Point' and buoyShape=8]" priority="3">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>27010</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="BOYSPR01"/>
      </pointInstruction>
      <xsl:if test="featureName!= ''">
         <textInstruction>
            <featureReference>
               <xsl:value-of select="@id"/>
            </featureReference>
            <viewingGroup>21</viewingGroup>
            <displayPlane>OVERRADAR</displayPlane>
            <drawingPriority>24</drawingPriority>
            <textPoint horizontalAlignment="End">
               <element>
                  <text>
                     <xsl:apply-templates select="featureName" mode="text">
                        <xsl:with-param name="prefix">by </xsl:with-param>
                     </xsl:apply-templates>
                  </text>
                  <xsl:call-template name="textStyle">
                     <xsl:with-param name="style">default</xsl:with-param>
                  </xsl:call-template>
               </element>
               <offset>
                  <x>-3.51</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoySpecialPurposeGeneral[@primitive='Point' and buoyShape=6]" priority="2">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>27010</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="BOYBAR01"/>
      </pointInstruction>
      <xsl:if test="featureName!= ''">
         <textInstruction>
            <featureReference>
               <xsl:value-of select="@id"/>
            </featureReference>
            <viewingGroup>21</viewingGroup>
            <displayPlane>OVERRADAR</displayPlane>
            <drawingPriority>24</drawingPriority>
            <textPoint horizontalAlignment="End">
               <element>
                  <text>
                     <xsl:apply-templates select="featureName" mode="text">
                        <xsl:with-param name="prefix">by </xsl:with-param>
                     </xsl:apply-templates>
                  </text>
                  <xsl:call-template name="textStyle">
                     <xsl:with-param name="style">default</xsl:with-param>
                  </xsl:call-template>
               </element>
               <offset>
                  <x>-3.51</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoySpecialPurposeGeneral[@primitive='Point' and buoyShape=7]" priority="2">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>27010</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="BOYSUP01"/>
      </pointInstruction>
      <xsl:if test="featureName!= ''">
         <textInstruction>
            <featureReference>
               <xsl:value-of select="@id"/>
            </featureReference>
            <viewingGroup>21</viewingGroup>
            <displayPlane>OVERRADAR</displayPlane>
            <drawingPriority>24</drawingPriority>
            <textPoint horizontalAlignment="End">
               <element>
                  <text>
                     <xsl:apply-templates select="featureName" mode="text">
                        <xsl:with-param name="prefix">by </xsl:with-param>
                     </xsl:apply-templates>
                  </text>
                  <xsl:call-template name="textStyle">
                     <xsl:with-param name="style">default</xsl:with-param>
                  </xsl:call-template>
               </element>
               <offset>
                  <x>-7.02</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoySpecialPurposeGeneral[@primitive='Point' and categoryOfSpecialPurposeMark=15]" priority="2">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>27010</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="LANBY"/>
      </pointInstruction>
      <xsl:if test="featureName!= ''">
         <textInstruction>
            <featureReference>
               <xsl:value-of select="@id"/>
            </featureReference>
            <viewingGroup>21</viewingGroup>
            <displayPlane>OVERRADAR</displayPlane>
            <drawingPriority>24</drawingPriority>
            <textPoint horizontalAlignment="End">
               <element>
                  <text>
                     <xsl:apply-templates select="featureName" mode="text">
                        <xsl:with-param name="prefix">by </xsl:with-param>
                     </xsl:apply-templates>
                  </text>
                  <xsl:call-template name="textStyle">
                     <xsl:with-param name="style">default</xsl:with-param>
                  </xsl:call-template>
               </element>
               <offset>
                  <x>-7.02</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoySpecialPurposeGeneral[@primitive='Point' and categoryOfSpecialPurposeMark=9]" priority="2">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>27010</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="ODAS 글자크기수정"/>
      </pointInstruction>
      <xsl:if test="featureName!= ''">
         <textInstruction>
            <featureReference>
               <xsl:value-of select="@id"/>
            </featureReference>
            <viewingGroup>21</viewingGroup>
            <displayPlane>OVERRADAR</displayPlane>
            <drawingPriority>24</drawingPriority>
            <textPoint horizontalAlignment="End">
               <element>
                  <text>
                     <xsl:apply-templates select="featureName" mode="text">
                        <xsl:with-param name="prefix">by </xsl:with-param>
                     </xsl:apply-templates>
                  </text>
                  <xsl:call-template name="textStyle">
                     <xsl:with-param name="style">default</xsl:with-param>
                  </xsl:call-template>
               </element>
               <offset>
                  <x>-7.02</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoySpecialPurposeGeneral[@primitive='Point']" priority="1">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>27025</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>21</drawingPriority>
         <symbol reference="DAYSQR21"/>
      </pointInstruction>
      <xsl:if test="featureName!= ''">
         <textInstruction>
            <featureReference>
               <xsl:value-of select="@id"/>
            </featureReference>
            <viewingGroup>27025</viewingGroup>
            <displayPlane>OVERRADAR</displayPlane>
            <drawingPriority>21</drawingPriority>
            <textPoint horizontalAlignment="End">
               <element>
                  <text>
                     <xsl:apply-templates select="featureName" mode="text">
                        <xsl:with-param name="prefix">bn </xsl:with-param>
                     </xsl:apply-templates>
                  </text>
                  <xsl:call-template name="textStyle">
                     <xsl:with-param name="style">default</xsl:with-param>
                  </xsl:call-template>
               </element>
               <offset>
                  <x>-3.51</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoySpecialPurposeGeneral[@primitive='Point' and topmark/topmarkDaymarkShape=24]" priority="2">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>27025</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>21</drawingPriority>
         <symbol reference="DAYTRI21"/>
      </pointInstruction>
      <xsl:if test="featureName!= ''">
         <textInstruction>
            <featureReference>
               <xsl:value-of select="@id"/>
            </featureReference>
            <viewingGroup>27025</viewingGroup>
            <displayPlane>OVERRADAR</displayPlane>
            <drawingPriority>21</drawingPriority>
            <textPoint horizontalAlignment="End">
               <element>
                  <text>
                     <xsl:apply-templates select="featureName" mode="text">
                        <xsl:with-param name="prefix">bn </xsl:with-param>
                     </xsl:apply-templates>
                  </text>
                  <xsl:call-template name="textStyle">
                     <xsl:with-param name="style">default</xsl:with-param>
                  </xsl:call-template>
               </element>
               <offset>
                  <x>-3.51</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoySpecialPurposeGeneral[@primitive='Point' and topmark/topmarkDaymarkShape=25]" priority="2">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>27025</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>21</drawingPriority>
         <symbol reference="DAYTRI25"/>
      </pointInstruction>
      <xsl:if test="featureName!= ''">
         <textInstruction>
            <featureReference>
               <xsl:value-of select="@id"/>
            </featureReference>
            <viewingGroup>27025</viewingGroup>
            <displayPlane>OVERRADAR</displayPlane>
            <drawingPriority>21</drawingPriority>
            <textPoint horizontalAlignment="End">
               <element>
                  <text>
                     <xsl:apply-templates select="featureName" mode="text">
                        <xsl:with-param name="prefix">bn </xsl:with-param>
                     </xsl:apply-templates>
                  </text>
                  <xsl:call-template name="textStyle">
                     <xsl:with-param name="style">default</xsl:with-param>
                  </xsl:call-template>
               </element>
               <offset>
                  <x>-3.51</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
</xsl:transform>
