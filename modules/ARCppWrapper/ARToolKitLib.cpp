#include <ARToolKitLib.hpp>
#include <iostream>


ARToolKitLib::ARToolKitLib(void)
{
	m_markerData = NULL;
}


ARToolKitLib::~ARToolKitLib(void)
{
    if( m_markerData != NULL )
		free( m_markerData );

	//argCleanup();
}

int ARToolKitLib::Initialization( char* strFileCameraParam, char* strFileMarker, int xsize, int ysize )
{
	//	char           *strFileCameraParam    = "Data/camera_para.dat";
	//	char            *strFileObject = "Data/object_data2";
	//	xsize = 640;
	//	ysize = 480;

	ARParam cparam;
	ARParam wparam;

    /* set the initial camera parameters */
    if( arParamLoad(strFileCameraParam, 1, &wparam) < 0 )
	{
        printf("Camera parameter load error !!\n");
		return -1;
        //exit(0);
    }

    arParamChangeSize( &wparam, xsize, ysize, &cparam );
    arInitCparam( &cparam );


	/* load in the object data - trained markers and associated bitmap files */
    if( ( m_markerData = ReadMarkerData(strFileMarker, &m_markerDataN) ) == NULL )
	{
        std::cout << "MARKER READ FAILED " << std::endl;
		return -1;
		//exit(0);
	}

    //printf("Objectfile num = %d\n", objectnum);

	return 0;
}

char* ARToolKitLib::get_buff( char *buf, int n, FILE *fp )
{
    char *ret;

    for(;;) {
        ret = fgets( buf, n, fp );
        if( ret == NULL ) return(NULL);
        if( buf[0] != '\n' && buf[0] != '#' ) return(ret);
    }
}

MarkerData_T* ARToolKitLib::ReadMarkerData( char *filename, int *markerDataN )
{
    FILE          *fp;
    char           buf[256], buf1[256];
    int            i;

	//printf("Opening Data File %s\n",name);

    if( ( fp = fopen(filename, "r") ) == NULL )
	{
		//printf("Can't find the file - quitting \n");
		return(0);
	}

    get_buff(buf, 256, fp);
    if( sscanf(buf, "%d", markerDataN) != 1 )
	{
		fclose(fp);
		return(0);
	}

	//printf("About to load %d Models\n",*objectnum);

    m_markerData = (MarkerData_T *)malloc( sizeof(MarkerData_T) * *markerDataN );
    if( m_markerData == NULL )
		return(0);

    for( i = 0; i < *markerDataN; i++ )
	{
		m_markerData[i].visible = 0;        
		
		get_buff(buf, 256, fp);
        if( sscanf(buf, "%s", m_markerData[i].type) != 1 )
		{
            fclose(fp);
			free(m_markerData);
			m_markerData = NULL;
			return(0);
        }

		get_buff(buf, 256, fp);
        if( sscanf(buf, "%s", m_markerData[i].name) != 1 )
		{
            fclose(fp);
			free(m_markerData);
			m_markerData = NULL;
			return(0);
        }

		//printf("Read in No.%d \n", i+1);

        get_buff(buf, 256, fp);
        if( sscanf(buf, "%s", buf1) != 1 )
		{
			fclose(fp);
			free(m_markerData);
			m_markerData = NULL;
			return(0);
		}
        
        if( (m_markerData[i].id = arLoadPatt(buf1)) < 0 )
        {
			fclose(fp);
			free(m_markerData);
			m_markerData = NULL;
			return(0);
		}

        get_buff(buf, 256, fp);
        if( sscanf(buf, "%lf", &m_markerData[i].marker_width) != 1 )
		{
            fclose(fp);
			free(m_markerData);
			m_markerData = NULL;
			return(0);
        }

        get_buff(buf, 256, fp);
        if( sscanf(buf, "%lf %lf", &m_markerData[i].marker_center[0], & m_markerData[i].marker_center[1]) != 2 )
		{
            fclose(fp);
			free(m_markerData);
			m_markerData = NULL;
			return(0);
        }

        get_buff(buf, 256, fp);
        if( sscanf(buf, "%lf %lf %lf", &m_markerData[i].rot_x, &m_markerData[i].rot_y, &m_markerData[i].rot_z ) != 3 )
		{
            fclose(fp);
			free(m_markerData);
			m_markerData = NULL;
			return(0);
        }

        get_buff(buf, 256, fp);
        if( sscanf(buf, "%lf %lf %lf", &m_markerData[i].trans_x, &m_markerData[i].trans_y, &m_markerData[i].trans_z ) != 3 )
		{
            fclose(fp);
			free(m_markerData);
			m_markerData = NULL;
			return(0);
        }

    }

    fclose(fp);

    return( m_markerData );
}

int ARToolKitLib::DetectMarker( ARUint8* dataPtr, int threshold )
{
	if( arDetectMarker( dataPtr, threshold, &m_markerInfo, &m_markerN ) < 0 )
		return -1;

	for( int i=0 ; i < m_markerDataN ; i++ )
	{
		int k = -1;
		for( int j=0 ; j < m_markerN ; j++ )
		{
	        if( m_markerData[i].id == m_markerInfo[j].id )
			{
				// you've found a pattern
				if( k == -1 )
					k = j;
		        else // make sure you have the best pattern (highest confidence factor)
				if( m_markerInfo[k].cf < m_markerInfo[j].cf )
					k = j;
			}
		}
		if( k == -1 )
		{
			m_markerData[i].visible = 0;
			continue;
		}
		
		// calculate the transform for each marker
		if( m_markerData[i].visible == 0 )
		{
            arGetTransMat(&m_markerInfo[k],
                          m_markerData[i].marker_center,
						  m_markerData[i].marker_width,
                          m_markerData[i].trans);
        }
        else
		{
            arGetTransMatCont(&m_markerInfo[k],
						  m_markerData[i].trans,
                          m_markerData[i].marker_center,
						  m_markerData[i].marker_width,
                          m_markerData[i].trans);
        }
        m_markerData[i].visible = 1;
	}

	return 1;
}
