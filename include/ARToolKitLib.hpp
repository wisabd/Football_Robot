#pragma once

#include <AR/gsub.h>
#include <AR/param.h>
#include <AR/ar.h>

typedef struct {
    char       type[256];
    char       name[256];
    int        id;
    int        visible;
	int		   collide;
    double     marker_coord[4][2];
    double     trans[3][4];
    double     marker_width;
    double     marker_center[2];
    double     rot_x, rot_y, rot_z;
    double     trans_x, trans_y, trans_z;
} MarkerData_T;

class ARToolKitLib
{
public:
	ARToolKitLib(void);
	virtual ~ARToolKitLib(void);
	int Initialization( char* strFileCameraParam, char* strFileMarker, int xsize, int ysize );
	char* get_buff( char *buf, int n, FILE *fp );
	MarkerData_T* ReadMarkerData( char *filename, int *markerDataN );

	int DetectMarker( ARUint8* dataPtr, int threshold = 100 );


	MarkerData_T* m_markerData;
	int m_markerDataN;

	ARMarkerInfo *m_markerInfo;
	int m_markerN;
};

