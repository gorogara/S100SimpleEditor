-- LightFogDetector portrayal rules file.

-- Referenced CSPs.
require 'LightFlareAndDescription'

-- Main entry point for feature type.
function LightFogDetector(feature, featurePortrayal, contextParameters)
	if contextParameters.RadarOverlay then
		featurePortrayal:AddInstructions('ViewingGroup:27070;DrawingPriority:24;DisplayPlane:OverRADAR')
	else
		featurePortrayal:AddInstructions('ViewingGroup:27070;DrawingPriority:24;DisplayPlane:UnderRADAR')
	end

	LightFlareAndDescription(feature, featurePortrayal, contextParameters, 7)
end
