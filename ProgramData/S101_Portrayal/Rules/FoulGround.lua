-- FoulGround portrayal rules file.

-- UNOFFICIAL:  Rules extracted from S-52 lookup table for OBSTRN where CATOBS = 7.

-- Main entry point for feature type.
function FoulGround(feature, featurePortrayal, contextParameters)
	if feature.PrimitiveType == PrimitiveType.Point and contextParameters.SimplifiedPoints then
		if feature.valueOfSounding then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:34051;DrawingPriority:4;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:34051;DrawingPriority:4;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:AddInstructions('PointInstruction:FOULGND1')
		else 
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:4;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:4;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:AddInstructions('PointInstruction:FOULGND1')
		end
	elseif feature.PrimitiveType == PrimitiveType.Point then
		if feature.valueOfSounding then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:34051;DrawingPriority:4;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:34051;DrawingPriority:4;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:AddInstructions('PointInstruction:FOULGND1')
		else
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:4;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:4;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:AddInstructions('PointInstruction:FOULGND1')
		end
	elseif feature.PrimitiveType == PrimitiveType.Curve then
		if contextParameters.RadarOverlay then
			featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:4;DisplayPlane:OverRADAR')
		else
			featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:4;DisplayPlane:UnderRADAR')
		end
		OBSTRN07(feature, featurePortrayal, contextParameters)
	elseif feature.PrimitiveType == PrimitiveType.Surface and contextParameters.PlainBoundaries then
		if feature.valueOfSounding then
			featurePortrayal:AddInstructions('ViewingGroup:34051;DrawingPriority:4;DisplayPlane:UnderRADAR')
			featurePortrayal:AddInstructions('PointInstruction:FOULGND1')
			featurePortrayal:SimpleLineStyle('dash',0.32,'CHGRD')
			featurePortrayal:AddInstructions('LineInstruction:_simple_')
		else
			featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:4;DisplayPlane:UnderRADAR')
			featurePortrayal:AddInstructions('PointInstruction:FOULGND1')
			featurePortrayal:SimpleLineStyle('dash',0.32,'CHGRD')
			featurePortrayal:AddInstructions('LineInstruction:_simple_')
		end
	elseif feature.PrimitiveType == PrimitiveType.Surface then
		if feature.valueOfSounding then
			featurePortrayal:AddInstructions('ViewingGroup:34051;DrawingPriority:4;DisplayPlane:UnderRADAR')
			featurePortrayal:AddInstructions('PointInstruction:FOULGND1')
			featurePortrayal:AddInstructions('LineInstruction:NAVARE51')
		else
			featurePortrayal:AddInstructions('ViewingGroup:34050;DrawingPriority:4;DisplayPlane:UnderRADAR')
			featurePortrayal:AddInstructions('PointInstruction:FOULGND1')
			featurePortrayal:AddInstructions('LineInstruction:NAVARE51')
		end
	else
		error('Invalid primitive type or mariner settings passed to portrayal')
	end
end
