-- SEABED01 conditional symbology rules file.

-- Main entry point for CSP.
function SEABED01(feature, featurePortrayal, contextParameters, depthRangeMinimumValue, depthRangeMaximumValue)
	Debug.StartPerformance('Lua Code - SEABED01')

	local Colour = 'DEPIT'
	local Shallow = true

	if (contextParameters.TwoShades) then
		if (depthRangeMinimumValue >= scaledDecimalZero and (not depthRangeMaximumValue or depthRangeMaximumValue > scaledDecimalZero)) then
			Colour = 'DEPVS'
		end

		if (depthRangeMinimumValue >= contextParameters.SafetyContour and (not depthRangeMaximumValue or depthRangeMaximumValue > contextParameters.SafetyContour)) then
			Colour = 'DEPDW'
			Shallow = false
		end
	else
		if (depthRangeMinimumValue >= scaledDecimalZero and (not depthRangeMaximumValue or depthRangeMaximumValue > scaledDecimalZero)) then
			Colour = 'DEPVS'
		end

		if (depthRangeMinimumValue >= contextParameters.ShallowContour and (not depthRangeMaximumValue or depthRangeMaximumValue > contextParameters.ShallowContour)) then
			Colour = 'DEPMS'
		end

		if (depthRangeMinimumValue >= contextParameters.SafetyContour and (not depthRangeMaximumValue or depthRangeMaximumValue > contextParameters.SafetyContour)) then
			Colour = 'DEPMD'
			Shallow = false
		end

		if (depthRangeMinimumValue >= contextParameters.DeepContour and (not depthRangeMaximumValue or depthRangeMaximumValue > contextParameters.DeepContour)) then
			Colour = 'DEPDW'
			Shallow = false
		end
	end

	--Debug.Trace('SEABED01: Colour = ' .. Colour .. ' SafetyContour = ' .. contextParameters.SafetyContour .. ' depthRangeMinimumValue = ' .. depthRangeMinimumValue .. ' depthRangeMaximumValue = ' .. depthRangeMaximumValue)

	featurePortrayal:AddInstructions('ColorFill:' .. Colour)

	if (contextParameters.ShallowPattern and Shallow) then
		featurePortrayal:AddInstructions('AreaFillReference:DIAMOND1')
	end

	Debug.StopPerformance('Lua Code - SEABED01')
end
