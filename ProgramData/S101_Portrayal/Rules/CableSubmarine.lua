-- Converter Version: 0.99
-- Feature Catalogue Version: 1.0.0 (2019/4/9)

-- Cable Submarine main entry point.
function CableSubmarine(feature, featurePortrayal, contextParameters)
	if feature.PrimitiveType == PrimitiveType.Curve then
		if feature.categoryOfCable == 6 then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:24010;DrawingPriority:18;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:24010;DrawingPriority:18;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:SimpleLineStyle('dash',0.32,'CHMGD')
			featurePortrayal:AddInstructions('LineInstruction:_simple_')
		else
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:34070;DrawingPriority:9;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:34070;DrawingPriority:9;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:AddInstructions('LineInstruction:CBLSUB06')
		end
	else
		error('Invalid primitive type or mariner settings passed to portrayal')
	end
end
