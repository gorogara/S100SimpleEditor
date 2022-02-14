<?xml version="1.0" encoding="UTF-8"?>

<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
   <xsl:output method="xml" encoding="UTF-8" indent="yes"/>
   <xsl:template match="BuoyLateral[@primitive='Point']" priority="1">
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
   <!-- buoyShape : conical (nun, ogival) -->
   <xsl:template match="BuoyLateral[@primitive='Point' and buoyShape=1]" priority="2">
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
   <!-- buoyShape : can (cylindrical) -->
   <xsl:template match="BuoyLateral[@primitive='Point' and buoyShape=2]" priority="2">
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
   <!-- buoyShape : spherical -->
   <xsl:template match="BuoyLateral[@primitive='Point' and buoyShape=3]" priority="2">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>27010</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="BOYSPH01"/>
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
   <!-- buoyShape : pillar -->
   <xsl:template match="BuoyLateral[@primitive='Point' and buoyShape=4]" priority="2">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>27010</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="BOYPIL01"/>
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
   <xsl:template match="BuoyLateral[@primitive='Point' and buoyShape=2 and categoryOfLateralMark=1]" priority="4">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="좌현(부표)"/>
      </pointInstruction>
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
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
                  <x>-7.02</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoyLateral[@primitive='Point' and buoyShape=4 and categoryOfLateralMark=1]" priority="4">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="좌현(pillar)"/>
      </pointInstruction>
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
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
                  <x>-7.02</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoyLateral[@primitive='Point' and buoyShape=5 and categoryOfLateralMark=1]" priority="4">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="좌현(spar)"/>
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
   <xsl:template match="BuoyLateral[@primitive='Point' and buoyShape=1 and categoryOfLateralMark=2]" priority="4">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="원추형 (홍)"/>
      </pointInstruction>
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
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
                  <x>-7.02</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoyLateral[@primitive='Point' and buoyShape=4 and categoryOfLateralMark=2]" priority="4">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="우현(pillar)"/>
      </pointInstruction>
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
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
                  <x>-7.02</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoyLateral[@primitive='Point' and buoyShape=5 and categoryOfLateralMark=2]" priority="4">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="우현(spar)"/>
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
   <xsl:template match="BuoyLateral[@primitive='Point' and buoyShape=2 and categoryOfLateralMark=4]" priority="4">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="원통형 (녹홍녹)"/>
      </pointInstruction>
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
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
                  <x>-7.02</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoyLateral[@primitive='Point' and buoyShape=4 and categoryOfLateralMark=4]" priority="4">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="우항로우선(pillar)"/>
      </pointInstruction>
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
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
                  <x>-7.02</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoyLateral[@primitive='Point' and buoyShape=5 and categoryOfLateralMark=4]" priority="4">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="우항로우선(spar)"/>
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
   <xsl:template match="BuoyLateral[@primitive='Point' and buoyShape=1 and categoryOfLateralMark=3]" priority="4">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="원추형 (홍녹홍)"/>
      </pointInstruction>
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
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
                  <x>-7.02</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoyLateral[@primitive='Point' and buoyShape=4 and categoryOfLateralMark=3]" priority="4">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="좌항로우선(pillar)"/>
      </pointInstruction>
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
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
                  <x>-7.02</x>
                  <y>3.51</y>
               </offset>
            </textPoint>
         </textInstruction>
      </xsl:if>
   </xsl:template>
   <xsl:template match="BuoyLateral[@primitive='Point' and buoyShape=5 and categoryOfLateralMark=3]" priority="4">
      <pointInstruction>
         <featureReference>
            <xsl:value-of select="@id"/>
         </featureReference>
         <viewingGroup>1</viewingGroup>
         <displayPlane>OVERRADAR</displayPlane>
         <drawingPriority>24</drawingPriority>
         <symbol reference="좌항로우선(spar)"/>
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
   <!-- buoyShape : spar (spindle) || ice buoy -->
   <xsl:template match="BuoyLateral[@primitive='Point' and (buoyShape=5 or buoyShape=8)]" priority="3">
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
   <!-- buoyShape : super-buoy -->
   <xsl:template match="BuoyLateral[@primitive='Point' and buoyShape=6]" priority="2">
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
   <!-- buoyShape : super-buoy -->
   <xsl:template match="BuoyLateral[@primitive='Point' and buoyShape=7]" priority="2">
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
</xsl:transform>
