#include "../GeoMetryLibrary/MBR.h"
#include "../GeoMetryLibrary/Geometry.h"
#include "../GeoMetryLibrary/GeoPoint.h"
#include "../GeoMetryLibrary/GeoPolygon.h"
#include "../GeoMetryLibrary/GeoPolyline.h"
#include "../GeoMetryLibrary/Scaler.h"
#include "../GeoMetryLibrary/GeoCommonFuc.h"

#include "Layer.h"
#include "LayerManager.h"
#include "SHPFile.h"
#include "SpatialObject.h"


#define GEOPOINT    1
#define GEOPOLYLINE 3
#define GEOPOLYGON  5

#define NAUTICAL_MILE 1852   
