<xsl:transform xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="xml" encoding="UTF-8" indent="yes"/>
  <xsl:template name="select_arrow_coverage">
    <xsl:param name="viewingGroup"/>
    <!--  The viewing group  -->
    <xsl:param name="displayPlane"/>
    <!--  The display plane  -->
    <xsl:param name="drawingPriority"/>
		<coverageInstruction>
      <featureReference>
       <xsl:value-of select="@id"/>
      </featureReference>			
			<viewingGroup>
				<xsl:value-of select="$viewingGroup"/>
			</viewingGroup>
			<displayPlane>
				<xsl:value-of select="$displayPlane"/>
			</displayPlane>
			<drawingPriority>
				<xsl:value-of select="$drawingPriority"/>
			</drawingPriority>
				<coverageFill>
					<attributeCode>surfaceCurrentSpeed</attributeCode>
						<lookup>
							<label>surfaceCurrentSpeedUndefined</label>
							<range>
								<xsl:attribute name="lower">-9999.0</xsl:attribute>
								<xsl:attribute name="upper">-9999.0</xsl:attribute>
								<xsl:attribute name="closure">closedInterval</xsl:attribute>  
							</range>
						</lookup>
						<lookup>
						  <label>surfaceCurrentSpeedLower</label>
						  <range>
							<xsl:attribute name="upper">0.01</xsl:attribute>
							<xsl:attribute name="closure">ltSemiInterval</xsl:attribute>
						  </range>
						  <symbol>
							<xsl:attribute name="reference">SCAROW01</xsl:attribute>
							<xsl:attribute name="defaultScaleFactor">0.4</xsl:attribute>
							<rotationAttribute>surfaceCurrentDirection</rotationAttribute>
						  </symbol>
						</lookup>
						<lookup>
							<label>surfaceCurrentSpeed1</label>
							<range>
								<xsl:attribute name="upper">0.49</xsl:attribute>
								<xsl:attribute name="closure">leSemiInterval</xsl:attribute>  
							</range>
							<symbol>
								<xsl:attribute name="reference">SCAROW01</xsl:attribute>
							    <xsl:attribute name="defaultScaleFactor">0.4</xsl:attribute>
								<rotationAttribute>surfaceCurrentDirection</rotationAttribute>
							</symbol>
						</lookup>
						<lookup>
							<label>surfaceCurrentSpeed2</label>
							<range>
								<xsl:attribute name="upper">0.99</xsl:attribute>
								<xsl:attribute name="closure">leSemiInterval</xsl:attribute>  
							</range>
							<symbol>
								<xsl:attribute name="reference">SCAROW02</xsl:attribute>							
							    <xsl:attribute name="defaultScaleFactor">0.4</xsl:attribute>
								<rotationAttribute>surfaceCurrentDirection</rotationAttribute>
							</symbol>
						</lookup>
						<lookup>
							<label>surfaceCurrentSpeed3</label>
							<range>
								<xsl:attribute name="upper">1.99</xsl:attribute>
								<xsl:attribute name="closure">leSemiInterval</xsl:attribute>  
							</range>
							<symbol>
								<xsl:attribute name="reference">SCAROW03</xsl:attribute>
							    <xsl:attribute name="defaultScaleFactor">0.4</xsl:attribute>
								<rotationAttribute>surfaceCurrentDirection</rotationAttribute>
							</symbol>
						</lookup>			
						<lookup>
							<label>surfaceCurrentSpeed4</label>
							<range>
								<xsl:attribute name="upper">2.99</xsl:attribute>
								<xsl:attribute name="closure">leSemiInterval</xsl:attribute>  
							</range>
							<symbol>
								<xsl:attribute name="reference">SCAROW04</xsl:attribute>							
								<rotationAttribute>surfaceCurrentDirection</rotationAttribute>
								<scaleAttribute>surfaceCurrentSpeed</scaleAttribute>
								<scaleFactor>0.2</scaleFactor>
							</symbol>
						</lookup>			
						<lookup>
							<label>surfaceCurrentSpeed5</label>
							<range>
								<xsl:attribute name="upper">4.99</xsl:attribute>
								<xsl:attribute name="closure">leSemiInterval</xsl:attribute>  
							</range>
							<symbol>
								<xsl:attribute name="reference">SCAROW05</xsl:attribute>							
								<rotationAttribute>surfaceCurrentDirection</rotationAttribute>
								<scaleAttribute>surfaceCurrentSpeed</scaleAttribute>
								<scaleFactor>0.2</scaleFactor>
							</symbol>
						</lookup>					
						<lookup>
							<label>surfaceCurrentSpeed6</label>
							<range>
								<xsl:attribute name="upper">6.99</xsl:attribute>
								<xsl:attribute name="closure">leSemiInterval</xsl:attribute>  
							</range>
							<symbol>
								<xsl:attribute name="reference">SCAROW06</xsl:attribute>							
								<rotationAttribute>surfaceCurrentDirection</rotationAttribute>
								<scaleAttribute>surfaceCurrentSpeed</scaleAttribute>
								<scaleFactor>0.2</scaleFactor>
							</symbol>
						</lookup>	
						<lookup>
							<label>surfaceCurrentSpeed7</label>
							<range>
								<xsl:attribute name="upper">9.99</xsl:attribute>
								<xsl:attribute name="closure">leSemiInterval</xsl:attribute>  
							</range>
							<symbol>
								<xsl:attribute name="reference">SCAROW07</xsl:attribute>							
								<rotationAttribute>surfaceCurrentDirection</rotationAttribute>2.6/1
								5<scaleAttribute>surfaceCurrentSpeed</scaleAttribute>
								<scaleFactor>0.2</scaleFactor>
							</symbol>
						</lookup>
						<lookup>
							<label>surfaceCurrentSpeed8</label>
							<range>
								<xsl:attribute name="upper">12.99</xsl:attribute>
								<xsl:attribute name="closure">leSemiInterval</xsl:attribute>  
							</range>
							<symbol>
								<xsl:attribute name="reference">SCAROW08</xsl:attribute>							
								<rotationAttribute>surfaceCurrentDirection</rotationAttribute>
								<scaleAttribute>surfaceCurrentSpeed</scaleAttribute>2.
								<scaleFactor>0.2</scaleFactor>
							</symbol>
						</lookup>			
						<lookup>
							<label>surfaceCurrentSpeedUpper</label>
							<range>
								<xsl:attribute name="lower">12.99</xsl:attribute>
								<xsl:attribute name="closure">gtSemiInterval</xsl:attribute>  
							</range>
							<symbol>
								<xsl:attribute name="reference">SCAROW09</xsl:attribute>	
								<xsl:attribute name="defaultScaleFactor">2.6</xsl:attribute>
								<rotationAttribute>surfaceCurrentDirection</rotationAttribute>
							</symbol>
						</lookup>			
			</coverageFill>
	</coverageInstruction>	
  </xsl:template>
</xsl:transform>