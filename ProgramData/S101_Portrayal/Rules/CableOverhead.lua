-- Converter Version: 0.99
-- Feature Catalogue Version: 1.0.0 (2019/4/9)

-- Cable Overhead main entry point.
function CableOverhead(feature, featurePortrayal, contextParameters)
	if feature.PrimitiveType == PrimitiveType.Curve then
		if feature.radarConspicuous and feature.verticalClearanceSafe and feature.verticalClearanceSafe.verticalClearanceValue then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:12210;DrawingPriority:24;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:12210;DrawingPriority:24;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:SimpleLineStyle('dash',1.28,'CHGRD')
			featurePortrayal:AddInstructions('LineInstruction:_simple_')
			featurePortrayal:AddInstructions('PointInstruction:RACNSP01')
			if feature.verticalClearanceSafe and feature.verticalClearanceSafe.verticalClearanceValue then
				featurePortrayal:AddInstructions('LocalOffset:3.51,0;FontSize:10;TextInstruction:' .. EncodeString(feature.verticalClearanceSafe.verticalClearanceValue, 'sf clr %4.1f') .. ',11,8')
			end
		elseif feature.radarConspicuous and feature.verticalClearanceSafe and feature.verticalClearanceSafe.verticalClearanceValue then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:12210;DrawingPriority:24;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:12210;DrawingPriority:24;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:SimpleLineStyle('dash',1.28,'CHGRD')
			featurePortrayal:AddInstructions('LineInstruction:_simple_')
			featurePortrayal:AddInstructions('PointInstruction:RACNSP01')
			if feature.verticalClearanceSafe and feature.verticalClearanceSafe.verticalClearanceValue then
				featurePortrayal:AddInstructions('LocalOffset:3.51,0;FontSize:10;TextInstruction:' .. EncodeString(feature.verticalClearanceSafe.verticalClearanceValue, 'sf clr %4.1f') .. ',11,8')
			end
		elseif feature.radarConspicuous and feature.verticalClearanceFixed and feature.verticalClearanceFixed.verticalClearanceValue then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:12210;DrawingPriority:24;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:12210;DrawingPriority:24;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:SimpleLineStyle('dash',1.28,'CHGRD')
			featurePortrayal:AddInstructions('LineInstruction:_simple_')
			featurePortrayal:AddInstructions('PointInstruction:RACNSP01')
			if feature.verticalClearanceFixed and feature.verticalClearanceFixed.verticalClearanceValue then
				featurePortrayal:AddInstructions('LocalOffset:3.51,0;FontSize:10;TextInstruction:' .. EncodeString(feature.verticalClearanceFixed.verticalClearanceValue, 'clr %4.1f') .. ',11,8')
			end
		elseif feature.radarConspicuous and feature.verticalClearanceFixed and feature.verticalClearanceFixed.verticalClearanceValue then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:12210;DrawingPriority:24;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:12210;DrawingPriority:24;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:SimpleLineStyle('dash',1.28,'CHGRD')
			featurePortrayal:AddInstructions('LineInstruction:_simple_')
			featurePortrayal:AddInstructions('PointInstruction:RACNSP01')
			if feature.verticalClearanceFixed and feature.verticalClearanceFixed.verticalClearanceValue then
				featurePortrayal:AddInstructions('LocalOffset:3.51,0;FontSize:10;TextInstruction:' .. EncodeString(feature.verticalClearanceFixed.verticalClearanceValue, 'clr %4.1f') .. ',11,8')
			end
		elseif feature.radarConspicuous then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:12210;DrawingPriority:24;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:12210;DrawingPriority:24;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:SimpleLineStyle('dash',1.28,'CHGRD')
			featurePortrayal:AddInstructions('LineInstruction:_simple_')
			featurePortrayal:AddInstructions('PointInstruction:RACNSP01')
		elseif feature.radarConspicuous then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:12210;DrawingPriority:24;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:12210;DrawingPriority:24;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:SimpleLineStyle('dash',1.28,'CHGRD')
			featurePortrayal:AddInstructions('LineInstruction:_simple_')
			featurePortrayal:AddInstructions('PointInstruction:RACNSP01')
		elseif feature.verticalClearanceSafe and feature.verticalClearanceSafe.verticalClearanceValue then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:12210;DrawingPriority:24;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:12210;DrawingPriority:24;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:SimpleLineStyle('dash',1.28,'CHGRD')
			featurePortrayal:AddInstructions('LineInstruction:_simple_')
			if feature.verticalClearanceSafe and feature.verticalClearanceSafe.verticalClearanceValue then
				featurePortrayal:AddInstructions('LocalOffset:3.51,0;FontSize:10;TextInstruction:' .. EncodeString(feature.verticalClearanceSafe.verticalClearanceValue, 'sf clr %4.1f') .. ',11,8')
			end
		elseif feature.verticalClearanceFixed and feature.verticalClearanceFixed.verticalClearanceValue then
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:12210;DrawingPriority:24;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:12210;DrawingPriority:24;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:SimpleLineStyle('dash',1.28,'CHGRD')
			featurePortrayal:AddInstructions('LineInstruction:_simple_')
			if feature.verticalClearanceFixed and feature.verticalClearanceFixed.verticalClearanceValue then
				featurePortrayal:AddInstructions('LocalOffset:3.51,0;FontSize:10;TextInstruction:' .. EncodeString(feature.verticalClearanceFixed.verticalClearanceValue, 'clr %4.1f') .. ',11,8')
			end
		else
			if contextParameters.RadarOverlay then
				featurePortrayal:AddInstructions('ViewingGroup:12210;DrawingPriority:24;DisplayPlane:OverRADAR')
			else
				featurePortrayal:AddInstructions('ViewingGroup:12210;DrawingPriority:24;DisplayPlane:UnderRADAR')
			end
			featurePortrayal:SimpleLineStyle('dash',1.28,'CHGRD')
			featurePortrayal:AddInstructions('LineInstruction:_simple_')
		end
	else
		error('Invalid primitive type or mariner settings passed to portrayal')
	end
end
