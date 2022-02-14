-- RESTRN01 conditional symbology rules file.

-- Referenced CSPs.
require 'RESCSP03'

-- Main entry point for CSP.
function RESTRN01(feature, featurePortrayal, contextParameters)
	Debug.StartPerformance('Lua Code - RESTRN01')
	
	size = #feature.restriction

	if size > 0 then
		RESCSP03(feature, featurePortrayal, contextParameters)
	end

	Debug.StopPerformance('Lua Code - RESTRN01')
end
