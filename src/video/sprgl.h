
#define COORD_A_U 0.0
#define COORD_A_V 0.0

#define COORD_B_U 1.0
#define COORD_B_V 0.0

#define COORD_C_U 1.0
#define COORD_C_V 1.0

#define COORD_D_U 0.0
#define COORD_D_V 1.0


#define SCALE_X (1.0f/(640.0f/VIDEO_GL_WIDTH))
#define MOVE_X (8.0f/(640.0f/VIDEO_GL_WIDTH))
#define SCALE_Y SCALE_X
#define MOVE_Y MOVE_X

#define VERTEX_1_X ((((float)sx)*SCALE_X))
#define VERTEX_1_Y ((((float)sy)*SCALE_Y)+MOVE_Y)
#define VERTEX_2_X ((((float)sx+(float)zx)*SCALE_X))
#define VERTEX_2_Y ((((float)sy)*SCALE_Y)+MOVE_Y)
#define VERTEX_3_X ((((float)sx+(float)zx)*SCALE_X))
#define VERTEX_3_Y ((((float)sy+(float)zy)*SCALE_Y)+MOVE_Y)
#define VERTEX_4_X ((((float)sx)*SCALE_X))
#define VERTEX_4_Y ((((float)sy+(float)zy)*SCALE_Y)+MOVE_Y)

#define GL_VERTICE(U,V,X,Y) \
	    glTexCoord2f(U,V); \
    	    glVertex3f(X,Y,tile_z);

#define GL_VERTICE_EOL(U,V,X,Y) GL_VERTICE(U,V,X,Y)

#define GL_VERTICE_FLIP_NONE \
   GL_VERTICE(COORD_A_U,COORD_A_V,VERTEX_1_X,VERTEX_1_Y) \
   GL_VERTICE(COORD_B_U,COORD_B_V,VERTEX_2_X,VERTEX_2_Y) \
   GL_VERTICE(COORD_C_U,COORD_C_V,VERTEX_3_X,VERTEX_3_Y) \
   GL_VERTICE_EOL(COORD_D_U,COORD_D_V,VERTEX_4_X,VERTEX_4_Y)

#define GL_VERTICE_FLIP_X \
   GL_VERTICE(COORD_B_U,COORD_B_V,VERTEX_1_X,VERTEX_1_Y) \
   GL_VERTICE(COORD_A_U,COORD_A_U,VERTEX_2_X,VERTEX_2_Y) \
   GL_VERTICE(COORD_D_U,COORD_D_V,VERTEX_3_X,VERTEX_3_Y) \
   GL_VERTICE_EOL(COORD_C_U,COORD_C_V,VERTEX_4_X,VERTEX_4_Y)

#define GL_VERTICE_FLIP_Y \
   GL_VERTICE(COORD_D_U,COORD_D_V,VERTEX_1_X,VERTEX_1_Y) \
   GL_VERTICE(COORD_C_U,COORD_C_V,VERTEX_2_X,VERTEX_2_Y) \
   GL_VERTICE(COORD_B_U,COORD_B_V,VERTEX_3_X,VERTEX_3_Y) \
   GL_VERTICE_EOL(COORD_A_U,COORD_A_V,VERTEX_4_X,VERTEX_4_Y) 

#define GL_VERTICE_FLIP_XY \
   GL_VERTICE(COORD_C_U,COORD_C_V,VERTEX_1_X,VERTEX_1_Y) \
   GL_VERTICE(COORD_D_U,COORD_C_V,VERTEX_2_X,VERTEX_2_Y) \
   GL_VERTICE(COORD_A_U,COORD_A_V,VERTEX_3_X,VERTEX_3_Y) \
   GL_VERTICE_EOL(COORD_B_U,COORD_B_V,VERTEX_4_X,VERTEX_4_Y)



#define VERTICE_INIT GL_VERTICE_INIT
#define VERTICE_INIT_EOL GL_VERTICE_INIT_EOL
#define _VERTICE_FLIP_XY GL_VERTICE_FLIP_XY 
#define _VERTICE_FLIP_X GL_VERTICE_FLIP_X 
#define _VERTICE_FLIP_Y GL_VERTICE_FLIP_Y 
#define _VERTICE_FLIP_NONE GL_VERTICE_FLIP_NONE 

#ifndef AES
#define VERTICE_FLIP_NONE _VERTICE_FLIP_NONE
#define VERTICE_FLIP_XY _VERTICE_FLIP_XY
#define VERTICE_FLIP_X _VERTICE_FLIP_X
#define VERTICE_FLIP_Y _VERTICE_FLIP_Y
#else
#define VERTICE_FLIP_NONE _VERTICE_FLIP_X
#define VERTICE_FLIP_XY _VERTICE_FLIP_Y
#define VERTICE_FLIP_X _VERTICE_FLIP_NONE
#define VERTICE_FLIP_Y _VERTICE_FLIP_XY
#endif

extern void *neo4all_texture_buffer;

