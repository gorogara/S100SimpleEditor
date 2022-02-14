#pragma once

class ENCPoint;
class GeoPolygon;
class GeoPolyline;
class GeoPoint;

class ENCPoint;
class ENCSounding;
class ENCLine;
class ENCArea;   

class GeometricFuc
{
public:
	GeometricFuc(void);
	virtual ~GeometricFuc(void);

public:
	static int intersect_equation(double p1x, double p1y, double p2x, double p2y, double p3x, double p3y, double p4x, double p4y);   
	static int intersect_ccw(double p1x, double p1y, double p2x, double p2y, double p3x, double p3y, double p4x, double p4y);
	static int intersect_ccw(GeoPolyline *objPoly, GeoPolygon *comPoly);
	static int intersect_ccw(GeoPolyline *objPoly, GeoPolyline *objPoly2); 
	static int intersect_ccw(ENCLine *objPoly, ENCArea *comPoly);
	static int intersect_ccw(ENCLine *objPoly, ENCLine *objPoly2);   
	static int ccw(double ax, double ay, double bx, double by, double cx, double cy);     
	static int overlap(double p1x, double p1y, GeoPolyline *comPoly, bool applyOption = false);
	static int overlap(GeoPolyline *objPoly, GeoPolyline *comPoly, bool applyOption = false);
	static int overlap(GeoPolyline *objPoly, GeoPolygon *comPoly, bool applyOption = false);
	static int overlap(GeoPolygon *objPoly, GeoPolygon *comPoly, bool applyOption = false); 
	static int overlap(double p1x, double p1y, ENCLine *comPoly, bool applyOption = false);
	static int overlap(GeoPoint *point, ENCLine *comPoly, bool applyOption = false);
	static int overlap(ENCPoint *objPoint, ENCLine *comPoly, bool applyOption = false);
	static int overlap(ENCLine *objPoly, ENCLine *comPoly, bool applyOption = false);
	static int overlap(ENCLine *objPoly, ENCArea *comPoly, bool applyOption = false);
	static int overlap(ENCArea *objPoly, ENCArea *comPoly, bool applyOption = false);       
	static int inside(GeoPoint *point, GeoPolygon *poly, bool applyOption = false);
	static int inside(double x, double y, GeoPolygon *poly, bool applyOption = false); 
	static int inside(ENCPoint *point, ENCArea *poly, bool applyOption = false);
	static int inside(double x, double y, ENCArea *poly, bool applyOption = false);     

};


void swap(double *var1, double *var2);