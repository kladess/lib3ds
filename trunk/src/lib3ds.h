/* -*- c -*- */
#ifndef INCLUDED_LIB3DS_H
#define INCLUDED_LIB3DS_H
/*
 * The 3D Studio File Format Library
 * Copyright (C) 1996-2007 by Jan Eric Kyprianidis <www.kyprianidis.com>
 * All rights reserved.
 *
 * This program is  free  software;  you can redistribute it and/or modify it
 * under the terms of the  GNU Lesser General Public License  as published by 
 * the  Free Software Foundation;  either version 2.1 of the License,  or (at 
 * your option) any later version.
 *
 * This  program  is  distributed in  the  hope that it will  be useful,  but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or  FITNESS FOR A  PARTICULAR PURPOSE.  See the  GNU Lesser General Public  
 * License for more details.
 *
 * You should  have received  a copy of the GNU Lesser General Public License
 * along with  this program;  if not, write to the  Free Software Foundation,
 * Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * $Id: types.h,v 1.25 2007/06/21 08:36:41 jeh Exp $
 */

#include <stddef.h>
#ifndef _MSC_VER
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#ifdef LIB3DS_EXPORTS
#define LIB3DSAPI __declspec(dllexport)
#else               
#define LIB3DSAPI __declspec(dllimport)
#endif           
#else
#define LIB3DSAPI
#endif

#ifdef _MSC_VER
typedef __int32 Lib3dsBool;
typedef unsigned __int8 Lib3dsByte;
typedef unsigned __int16 Lib3dsWord;
typedef unsigned __int32 Lib3dsDword;
typedef signed __int8 Lib3dsIntb;
typedef signed __int16 Lib3dsIntw;
typedef signed __int16 Lib3dsIntd;
#else
typedef int32_t Lib3dsBool;
typedef uint8_t Lib3dsByte;
typedef uint16_t Lib3dsWord;
typedef uint32_t Lib3dsDword;
typedef int8_t Lib3dsIntb;
typedef int16_t Lib3dsIntw;
typedef int32_t Lib3dsIntd;
#endif

typedef union Lib3dsUserData {
    void *p;
    Lib3dsIntd i;
    Lib3dsDword d;
    float f;
} Lib3dsUserData;

typedef float Lib3dsVector[3];          
typedef float Lib3dsQuat[4];            
typedef float Lib3dsMatrix[4][4];       
typedef float Lib3dsRgb[3];             
                
typedef enum Lib3dsIoSeek {
  LIB3DS_SEEK_SET  =0,
  LIB3DS_SEEK_CUR  =1,
  LIB3DS_SEEK_END  =2
} Lib3dsIoSeek;

typedef enum Lib3dsLogLevel {
    LIB3DS_LOG_ERROR    = 0,
    LIB3DS_LOG_WARN     = 1,
    LIB3DS_LOG_INFO     = 2,
    LIB3DS_LOG_DEBUG    = 3
} Lib3dsLogLevel;

typedef struct Lib3dsIo Lib3dsIo;
typedef Lib3dsBool (*Lib3dsIoErrorFunc)(void *self);
typedef long (*Lib3dsIoSeekFunc)(void *self, long offset, Lib3dsIoSeek origin);
typedef long (*Lib3dsIoTellFunc)(void *self);
typedef size_t (*Lib3dsIoReadFunc)(void *self, void *buffer, size_t size);
typedef size_t (*Lib3dsIoWriteFunc)(void *self, const void *buffer, size_t size);
typedef void (*Lib3dsIoLogFunc)(Lib3dsIo *io, Lib3dsLogLevel level, char *msg);

/*!
 * Fog atmosphere settings
 */
typedef struct Lib3dsFog {
    Lib3dsBool use;
    Lib3dsRgb col;
    Lib3dsBool fog_background;
    float near_plane;
    float near_density;
    float far_plane;
    float far_density;
} Lib3dsFog;

/*!
 * Layer fog atmosphere flags
 */
typedef enum Lib3dsLayerFogFlags {
  LIB3DS_BOTTOM_FALL_OFF =0x00000001,
  LIB3DS_TOP_FALL_OFF    =0x00000002,
  LIB3DS_FOG_BACKGROUND  =0x00100000
} Lib3dsLayerFogFlags;

/*!
 * Layer fog atmosphere settings
 */
typedef struct Lib3dsLayerFog {
    Lib3dsBool use;
    Lib3dsDword flags;
    Lib3dsRgb col;
    float near_y;
    float far_y;
    float density;
} Lib3dsLayerFog;

/*!
 * Distance cue atmosphere settings
 */
typedef struct Lib3dsDistanceCue {
    Lib3dsBool use;
    Lib3dsBool cue_background;
    float near_plane;
    float near_dimming;
    float far_plane;
    float far_dimming;
} Lib3dsDistanceCue;

/*!
 * Atmosphere settings
 */
typedef struct Lib3dsAtmosphere {
    Lib3dsFog fog;
    Lib3dsLayerFog layer_fog;
    Lib3dsDistanceCue dist_cue;
} Lib3dsAtmosphere;

/*!
 * Bitmap background settings
 */
typedef struct Lib3dsBitmap {
    Lib3dsBool use;
    char name[64];
} Lib3dsBitmap;

/*!
 * Solid color background settings
 */
typedef struct Lib3dsSolid {
    Lib3dsBool use;
    Lib3dsRgb col;
} Lib3dsSolid;

/*!
 * Gradient background settings
 */
typedef struct Lib3dsGradient {
    Lib3dsBool use;
    float percent;
    Lib3dsRgb top;
    Lib3dsRgb middle;
    Lib3dsRgb bottom;
} Lib3dsGradient;

/*!
 * Background settings
 */
typedef struct Lib3dsBackground {
    Lib3dsBitmap bitmap;
    Lib3dsSolid solid;
    Lib3dsGradient gradient;
} Lib3dsBackground;

/*!
 * Shadow map settings
 */
typedef struct Lib3dsShadow {
    Lib3dsIntw map_size;
    float lo_bias;
    float hi_bias;
    Lib3dsIntw samples;
    Lib3dsIntd range;
    float filter;
    float ray_bias;
} Lib3dsShadow;

/*!
 * Layout view types
 */
typedef enum Lib3dsViewType {
    LIB3DS_VIEW_TYPE_NOT_USED  =0,
    LIB3DS_VIEW_TYPE_TOP       =1,
    LIB3DS_VIEW_TYPE_BOTTOM    =2,
    LIB3DS_VIEW_TYPE_LEFT      =3,
    LIB3DS_VIEW_TYPE_RIGHT     =4,
    LIB3DS_VIEW_TYPE_FRONT     =5,
    LIB3DS_VIEW_TYPE_BACK      =6,
    LIB3DS_VIEW_TYPE_USER      =7,
    LIB3DS_VIEW_TYPE_SPOTLIGHT =18,
    LIB3DS_VIEW_TYPE_CAMERA    =65535
} Lib3dsViewType;

/*!
 * Layout view settings
 */
typedef struct Lib3dsView {
    Lib3dsWord type;
    Lib3dsWord axis_lock;
    Lib3dsIntw position[2];
    Lib3dsIntw size[2];
    float zoom;
    Lib3dsVector center;
    float horiz_angle;
    float vert_angle;
    char camera[11];
} Lib3dsView;

/*!
 * Layout styles
 */
typedef enum Lib3dsLayoutStyle {
    LIB3DS_LAYOUT_SINGLE                  =0,
    LIB3DS_LAYOUT_TWO_PANE_VERT_SPLIT     =1,
    LIB3DS_LAYOUT_TWO_PANE_HORIZ_SPLIT    =2,
    LIB3DS_LAYOUT_FOUR_PANE               =3,
    LIB3DS_LAYOUT_THREE_PANE_LEFT_SPLIT   =4,
    LIB3DS_LAYOUT_THREE_PANE_BOTTOM_SPLIT =5,
    LIB3DS_LAYOUT_THREE_PANE_RIGHT_SPLIT  =6,
    LIB3DS_LAYOUT_THREE_PANE_TOP_SPLIT    =7,
    LIB3DS_LAYOUT_THREE_PANE_VERT_SPLIT   =8,
    LIB3DS_LAYOUT_THREE_PANE_HORIZ_SPLIT  =9,
    LIB3DS_LAYOUT_FOUR_PANE_LEFT_SPLIT    =10,
    LIB3DS_LAYOUT_FOUR_PANE_RIGHT_SPLIT   =11
} Lib3dsLayoutStyle;


#define LIB3DS_LAYOUT_MAX_VIEWS 32

/*!
 * Viewport layout settings
 */
typedef struct Lib3dsLayout {
    Lib3dsWord style;
    Lib3dsIntw active;
    Lib3dsIntw swap;
    Lib3dsIntw swap_prior;
    Lib3dsIntw swap_view;
    Lib3dsWord position[2];
    Lib3dsWord size[2];
    Lib3dsDword nviews;
    Lib3dsView views[LIB3DS_LAYOUT_MAX_VIEWS];
} Lib3dsLayout;

/*!
 * Default view settings
 */
typedef struct Lib3dsDefaultView {
    Lib3dsWord type;
    Lib3dsVector position;
    float width;
    float horiz_angle;
    float vert_angle;
    float roll_angle;
    char camera[64];
} Lib3dsDefaultView;

/*!
 * Viewport and default view settings
 */
typedef struct Lib3dsViewport {
    Lib3dsLayout layout;
    Lib3dsDefaultView default_view;
} Lib3dsViewport;

/*!
 * Material texture map flags
 */
typedef enum Lib3dsTextureMapFlags {
  LIB3DS_DECALE       =0x0001,
  LIB3DS_MIRROR       =0x0002,
  LIB3DS_NEGATE       =0x0008,
  LIB3DS_NO_TILE      =0x0010,
  LIB3DS_SUMMED_AREA  =0x0020,
  LIB3DS_ALPHA_SOURCE =0x0040,
  LIB3DS_TINT         =0x0080,
  LIB3DS_IGNORE_ALPHA =0x0100,
  LIB3DS_RGB_TINT     =0x0200
} Lib3dsTextureMapFlags;

/*!
 * Material texture map
 */
typedef struct Lib3dsTextureMap {
    Lib3dsUserData user;
    char name[64];
    Lib3dsDword flags;
    float percent;
    float blur;
    float scale[2];
    float offset[2];
    float rotation;
    Lib3dsRgb tint_1;
    Lib3dsRgb tint_2;
    Lib3dsRgb tint_r;
    Lib3dsRgb tint_g;
    Lib3dsRgb tint_b;
} Lib3dsTextureMap;

/*!
 * Auto reflection texture map flags.
 */
typedef enum Lib3dsAutoReflMapFlags {
    LIB3DS_USE_REFL_MAP          =0x0001,
    LIB3DS_READ_FIRST_FRAME_ONLY =0x0004,
    LIB3DS_FLAT_MIRROR           =0x0008 
} Lib3dsAutoReflectionMapFlags;

/*!
 * Auto reflection texture map antialiasing level.
 */
typedef enum Lib3dsAutoReflMapAntiAliasLevel {
    LIB3DS_ANTI_ALIAS_NONE   =0,
    LIB3DS_ANTI_ALIAS_LOW    =1,
    LIB3DS_ANTI_ALIAS_MEDIUM =2,
    LIB3DS_ANTI_ALIAS_HIGH   =3
} Lib3dsAutoReflMapAntiAliasLevel;

/*!
 * Auto reflection map settings
 */
typedef struct Lib3dsAutoReflMap {
    Lib3dsDword flags;
    Lib3dsIntd level;
    Lib3dsIntd size;
    Lib3dsIntd frame_step;
} Lib3dsAutoReflMap;

/*!
 * Material shading type. 
 */
typedef enum Lib3dsMaterialShading {
      LIB3DS_WIRE_FRAME =0,
      LIB3DS_FLAT       =1, 
      LIB3DS_GOURAUD    =2, 
      LIB3DS_PHONG      =3, 
      LIB3DS_METAL      =4
} Lib3dsMaterialShading; 

/*!
 * Material
 */
typedef struct Lib3dsMaterial {
    Lib3dsUserData user;		/* Arbitrary user data */
    char name[64];			    /* Material name */
    Lib3dsRgb ambient;			/* Material ambient reflectivity */
    Lib3dsRgb diffuse;			/* Material diffuse reflectivity */
    Lib3dsRgb specular;		    /* Material specular reflectivity */
    float shininess;		    /* Material specular exponent */
    float shin_strength;
    Lib3dsBool use_blur;
    float blur;
    float transparency;
    float falloff;
    Lib3dsBool additive;
    float self_ilpct;
    Lib3dsBool use_falloff;
    Lib3dsBool self_illum;
    Lib3dsIntw shading;
    Lib3dsBool soften;
    Lib3dsBool face_map;
    Lib3dsBool two_sided;		/* Material visible from back */
    Lib3dsBool map_decal;
    Lib3dsBool use_wire;
    Lib3dsBool use_wire_abs;
    float wire_size;
    Lib3dsTextureMap texture1_map;
    Lib3dsTextureMap texture1_mask;
    Lib3dsTextureMap texture2_map;
    Lib3dsTextureMap texture2_mask;
    Lib3dsTextureMap opacity_map;
    Lib3dsTextureMap opacity_mask;
    Lib3dsTextureMap bump_map;
    Lib3dsTextureMap bump_mask;
    Lib3dsTextureMap specular_map;
    Lib3dsTextureMap specular_mask;
    Lib3dsTextureMap shininess_map;
    Lib3dsTextureMap shininess_mask;
    Lib3dsTextureMap self_illum_map;
    Lib3dsTextureMap self_illum_mask;
    Lib3dsTextureMap reflection_map;
    Lib3dsTextureMap reflection_mask;
    Lib3dsAutoReflMap autorefl_map;
} Lib3dsMaterial;

/*!
 * Object flags for cameras, lights and meshes.
 */
typedef enum Lib3dsObjectFlags {
    LIB3DS_OBJECT_HIDDEN          =0x01, 
    LIB3DS_OBJECT_VIS_LOFTER      =0x02, 
    LIB3DS_OBJECT_DOESNT_CAST     =0x04, 
    LIB3DS_OBJECT_MATTE           =0x08, 
    LIB3DS_OBJECT_DONT_RCVSHADOW  =0x10, 
    LIB3DS_OBJECT_FAST            =0x20, 
    LIB3DS_OBJECT_FROZEN          =0x40 
} Lib3dsObjectFlags;

/*!
 * Camera object
 */
typedef struct Lib3dsCamera {
    Lib3dsUserData user;
    char name[64];
    Lib3dsDword object_flags; /*< @see Lib3dsObjectFlags */ 
    Lib3dsVector position;
    Lib3dsVector target;
    float roll;
    float fov;
    Lib3dsBool see_cone;
    float near_range;
    float far_range;
} Lib3dsCamera; 

/*!
 * Light object
 */
typedef struct Lib3dsLight {
    Lib3dsUserData user;
    char name[64];
    Lib3dsDword object_flags; /*< @see Lib3dsObjectFlags */ 
    Lib3dsBool spot_light;
    Lib3dsBool see_cone;
    Lib3dsRgb color;
    Lib3dsVector position;
    Lib3dsVector spot;
    float roll;
    Lib3dsBool off;
    float outer_range;
    float inner_range;
    float multiplier;
    /*const char** excludes;*/
    float attenuation;
    Lib3dsBool rectangular_spot;
    Lib3dsBool shadowed;
    float shadow_bias;
    float shadow_filter;
    Lib3dsIntw shadow_size;
    float spot_aspect;
    Lib3dsBool use_projector;
    char projector[64];
    Lib3dsIntd spot_overshoot;
    Lib3dsBool ray_shadows;
    float ray_bias;
    float hot_spot;
    float fall_off;
} Lib3dsLight; 

/*!
 * Triangular mesh face
 */
typedef struct Lib3dsFace {
    Lib3dsIntd material;    /**< Material index */
    Lib3dsWord index[3];	/**< Indices into mesh points list */
    Lib3dsWord flags;		/**< \sa Lib3dsFaceFlag */
    Lib3dsDword smoothing;	/**< Bitmask; each bit identifies a group */
} Lib3dsFace;

/*!
 * Vertex flags
 * Meaning of _Lib3dsFace::flags. ABC are points of the current face 
 * (A: is 1st vertex, B is 2nd vertex, C is 3rd vertex) 
 */
typedef enum {
  LIB3DS_FACE_FLAG_VIS_AC = 0x1,       /**< Bit 0: Edge visibility AC */
  LIB3DS_FACE_FLAG_VIS_BC = 0x2,       /**< Bit 1: Edge visibility BC */
  LIB3DS_FACE_FLAG_VIS_AB = 0x4,       /**< Bit 2: Edge visibility AB */
  LIB3DS_FACE_FLAG_WRAP_U = 0x8,       /**< Bit 3: Face is at tex U wrap seam */
  LIB3DS_FACE_FLAG_WRAP_V = 0x10,      /**< Bit 4: Face is at tex V wrap seam */
  LIB3DS_FACE_FLAG_UNK7 = 0x80,        /* Bit 5-8: Unused ? */
  LIB3DS_FACE_FLAG_UNK10 = 0x400,      /* Bit 9-10: Random ? */
                                       /* Bit 11-12: Unused ? */
  LIB3DS_FACE_FLAG_SELECT_3 = (1<<13),   /**< Bit 13: Selection of the face in selection 3*/
  LIB3DS_FACE_FLAG_SELECT_2 = (1<<14),   /**< Bit 14: Selection of the face in selection 2*/
  LIB3DS_FACE_FLAG_SELECT_1 = (1<<15),   /**< Bit 15: Selection of the face in selection 1*/
} Lib3dsFaceFlag;

typedef float Lib3dsTexco[2];

/*!
 * Triangular mesh box mapping settings
 */
typedef struct Lib3dsBoxMap {
    char front[64];
    char back[64];
    char left[64];
    char right[64];
    char top[64];
    char bottom[64];
} Lib3dsBoxMap;

/*!
 * Texture projection type
 */
typedef enum {
  LIB3DS_MAP_NONE        =0xFFFF,
  LIB3DS_MAP_PLANAR      =0,
  LIB3DS_MAP_CYLINDRICAL =1,
  LIB3DS_MAP_SPHERICAL   =2
} Lib3dsMapType;

/*!
 * Triangular mesh texture mapping data
 */
typedef struct Lib3dsMapData {
    Lib3dsWord maptype;
    Lib3dsVector pos;
    Lib3dsMatrix matrix;
    float scale;
    float tile[2];
    float planar_size[2];
    float cylinder_height;
} Lib3dsMapData;

/*!
 * Triangular mesh object
 */
typedef struct Lib3dsMesh {
    Lib3dsUserData user;    	/*< Arbitrary user data */
    char name[64];		        /*< Mesh name. Don't use more than 8 characters  */
    Lib3dsDword object_flags;   /*< @see Lib3dsObjectFlags */ 
    Lib3dsByte color;
    Lib3dsMatrix matrix;    	/*< Transformation matrix for mesh data */
    Lib3dsWord nvertices;		/*< Number of points in point list */
    Lib3dsVector *vertices;	    /*< Point list */
    Lib3dsWord nflags;		    /*< Number of flags in per-point flags list */
    Lib3dsWord *flags;		    /*< Per-point flags list */
    Lib3dsWord ntexcos;		    /*< Number of U-V texture coordinates */
    Lib3dsTexco *texcos;	    /*< U-V texture coordinates */
    Lib3dsWord nfaces;	        /*< Number of faces in face list */
    Lib3dsFace *faces;		    /*< Face list */
    Lib3dsBoxMap box_map;
    Lib3dsMapData map_data;
} Lib3dsMesh; 

typedef enum Lib3dsTcbFlags{
    LIB3DS_USE_TENSION    =0x0001,
    LIB3DS_USE_CONTINUITY =0x0002,
    LIB3DS_USE_BIAS       =0x0004,
    LIB3DS_USE_EASE_TO    =0x0008,
    LIB3DS_USE_EASE_FROM  =0x0010
} Lib3dsTcbFlags;

typedef struct Lib3dsTcb {
    Lib3dsWord flags;
    float tens;
    float cont;
    float bias;
    float ease_to;
    float ease_from;
} Lib3dsTcb;

typedef enum {
    LIB3DS_REPEAT    = 0x0001,
    LIB3DS_SMOOTH    = 0x0002,
    LIB3DS_LOCK_X    = 0x0008,
    LIB3DS_LOCK_Y    = 0x0010,
    LIB3DS_LOCK_Z    = 0x0020,
    LIB3DS_UNLINK_X  = 0x0100,
    LIB3DS_UNLINK_Y  = 0x0200,
    LIB3DS_UNLINK_Z  = 0x0400
} Lib3dsTrackFlags;

typedef enum Lib3dsTrackType {
    LIB3DS_TRACK_UNKNOWN = 0,
    LIB3DS_TRACK_BOOL    = 1,
    LIB3DS_TRACK_FLOAT   = 2,
    LIB3DS_TRACK_VECTOR  = 3,
    LIB3DS_TRACK_QUAT    = 4,
    LIB3DS_TRACK_MORPH   = 5,
} Lib3dsTrackType;

typedef struct Lib3dsFloatKeyData {
    float value;
    float dd;
    float ds;
} Lib3dsFloatKeyData;

typedef struct Lib3dsVectorKeyData {
    Lib3dsVector value;
    Lib3dsVector dd;
    Lib3dsVector ds;
} Lib3dsVectorKeyData;

typedef struct Lib3dsQuatKeyData {
    float angle;
    Lib3dsQuat axis;
    Lib3dsQuat quat;
    Lib3dsQuat a;
    Lib3dsQuat b;
} Lib3dsQuatKeyData;

typedef struct Lib3dsMorphKeyData {
    char name[64];
} Lib3dsMorphKeyData;

typedef union Lib3dsKeyData {
    Lib3dsFloatKeyData f;
    Lib3dsVectorKeyData v;
    Lib3dsQuatKeyData q;
    Lib3dsMorphKeyData m;
} Lib3dsKeyData;

typedef struct Lib3dsKey {
    Lib3dsIntd frame;
    Lib3dsTcb tcb;
    Lib3dsKeyData data;
} Lib3dsKey;

typedef struct Lib3dsTrack {
    Lib3dsDword flags;
    Lib3dsTrackType type; 
    Lib3dsDword nkeys;
    Lib3dsKey *keys;   
} Lib3dsTrack;

typedef enum Lib3dsNodeType {
    LIB3DS_UNKNOWN_NODE = 0,
    LIB3DS_AMBIENT_NODE = 1,
    LIB3DS_OBJECT_NODE  = 2,
    LIB3DS_CAMERA_NODE  = 3,
    LIB3DS_TARGET_NODE  = 4,
    LIB3DS_LIGHT_NODE   = 5,
    LIB3DS_SPOT_NODE    = 6
} Lib3dsNodeType;

/*!
 * Scene graph ambient color node data
 */
typedef struct Lib3dsAmbientData {
    Lib3dsRgb col;
    Lib3dsTrack *col_track;
} Lib3dsAmbientData;

/*!
 * Scene graph object instance node data
 */
typedef struct Lib3dsObjectData {
    Lib3dsVector pivot;
    char instance[64];
    Lib3dsVector bbox_min;
    Lib3dsVector bbox_max;
    Lib3dsBool hide;
    Lib3dsVector pos;
    Lib3dsQuat rot;
    Lib3dsVector scl;
    float morph_smooth;
    char morph[64];
    Lib3dsTrack *pos_track;
    Lib3dsTrack *rot_track;
    Lib3dsTrack *scl_track;
    Lib3dsTrack *morph_track;
    Lib3dsTrack *hide_track;
} Lib3dsObjectData;

/*!
 * Scene graph camera node data
 */
typedef struct Lib3dsCameraData {
    Lib3dsVector pos;
    float fov;
    float roll;
    Lib3dsTrack *pos_track;
    Lib3dsTrack *fov_track;
    Lib3dsTrack *roll_track;
} Lib3dsCameraData;

/*!
 * Scene graph camera target node data
 */
typedef struct Lib3dsTargetData {
    Lib3dsVector pos;
    Lib3dsTrack *pos_track;
} Lib3dsTargetData;

/*!
 * Scene graph light node data
 */
typedef struct Lib3dsLightData {
    Lib3dsVector pos;
    Lib3dsRgb col;
    float hotspot;
    float falloff;
    float roll;
    Lib3dsTrack *pos_track;
    Lib3dsTrack *col_track;
    Lib3dsTrack *hotspot_track;
    Lib3dsTrack *falloff_track;
    Lib3dsTrack *roll_track;
} Lib3dsLightData;

/*!
 * Scene graph spotlight target node data
 */
typedef struct Lib3dsSpotData {
    Lib3dsVector pos;
    Lib3dsTrack *pos_track;
} Lib3dsSpotData;

/*!
 * Scene graph node data union
 */
typedef union Lib3dsNodeData {
    Lib3dsAmbientData ambient;
    Lib3dsObjectData object;
    Lib3dsCameraData camera;
    Lib3dsTargetData target;
    Lib3dsLightData light;
    Lib3dsSpotData spot;
} Lib3dsNodeData;

#define LIB3DS_NO_PARENT 65535

/*!
 * Node flags #1
 */
typedef enum {
    LIB3DS_HIDDEN = 0x800
} Lib3dsNodeFlags1;

/*!
 * Node flags #2
 */
typedef enum {
    LIB3DS_SHOW_PATH = 0x1,
    LIB3DS_SMOOTHING = 0x2,
    LIB3DS_MOTION_BLUR = 0x10,
    LIB3DS_MORPH_MATERIALS = 0x40
} Lib3dsNodeFlags2;

/*!
 * Scene graph node
 */
typedef struct Lib3dsNode {
    Lib3dsUserData user;
    struct Lib3dsNode *next;
    struct Lib3dsNode *childs;
    struct Lib3dsNode *parent;
    Lib3dsNodeType type;
    Lib3dsWord node_id;
    char name[64];
    Lib3dsWord flags1;
    Lib3dsWord flags2;
    Lib3dsWord parent_id;
    Lib3dsMatrix matrix;
    Lib3dsNodeData data;
} Lib3dsNode;

/*!
    3DS file structure 
 */
typedef struct Lib3dsFile {
    Lib3dsUserData user;
    Lib3dsDword mesh_version;
    Lib3dsWord keyf_revision;
    char name[12+1];
    float master_scale;
    Lib3dsVector construction_plane;
    Lib3dsRgb ambient;
    Lib3dsShadow shadow;
    Lib3dsBackground background;
    Lib3dsAtmosphere atmosphere;
    Lib3dsViewport viewport;
    Lib3dsViewport viewport_keyf;
    Lib3dsIntd frames;
    Lib3dsIntd segment_from;
    Lib3dsIntd segment_to;
    Lib3dsIntd current_frame;
    Lib3dsIntd materials_size;
    Lib3dsIntd nmaterials;                      
    Lib3dsMaterial **materials;
    Lib3dsIntd cameras_size;
    Lib3dsIntd ncameras;                      
    Lib3dsCamera **cameras;
    Lib3dsIntd lights_size;
    Lib3dsIntd nlights;                      
    Lib3dsLight **lights;
    Lib3dsIntd meshes_size;
    Lib3dsIntd nmeshes;                      
    Lib3dsMesh **meshes;                         
    Lib3dsNode *nodes;
} Lib3dsFile; 


/*! @functiongroup Floating Point Math */

/*! 
    @function lib3ds_float_ease
        Calculates the ease in/out function.
    @param fp
        [in] Previous frame number.
    @param fp
        [in] Current frame number.
    @param fp
        [in] Next frame number.
    @param ease_from
        [in] Ease in value [0, 1.0]
    @param ease_to
        [in] Ease out value [0, 1.0]
    @return
        The calculated value of the function.
 */
extern LIB3DSAPI float lib3ds_float_ease(
    float fp, 
    float fc, 
    float fn, 
    float ease_from, 
    float ease_to);

/*! 
    @function lib3ds_float_cubic
    @param a
        [in] First point.
    @param p
        [in] Tangent of first point.
    @param q
        [in] Tangent of second point.
    @param b
        [in] Second point.
    @param t
        [in] 
 */
extern LIB3DSAPI float lib3ds_float_cubic(
    float a, 
    float p, 
    float q, 
    float b, 
    float t);

/*! @functiongroup Vector Math */

/*! 
    @function lib3ds_vector_zero 
        Sets all components of a vector to zero.
    @param c
         [in/out] The pointer to the vector. 
 */
extern LIB3DSAPI void lib3ds_vector_zero(
    Lib3dsVector c );

/*! 
    @function lib3ds_vector_copy 
        Copies all components of a vector to another vector.
    @param dst
        [out] The destination vector.
    @param src
        [in] The source vector. 
 */
extern LIB3DSAPI void lib3ds_vector_copy( 
    Lib3dsVector dest, 
    Lib3dsVector src );

/*! 
    @function lib3ds_vector_neg
        Negates all components of a vector.
    @param c
        [in/out] The pointer to the vector. 
 */
extern LIB3DSAPI void lib3ds_vector_neg(
    Lib3dsVector c);

extern LIB3DSAPI void lib3ds_vector_add(Lib3dsVector c, Lib3dsVector a, Lib3dsVector b);
extern LIB3DSAPI void lib3ds_vector_sub(Lib3dsVector c, Lib3dsVector a, Lib3dsVector b);
extern LIB3DSAPI void lib3ds_vector_scalar(Lib3dsVector c, float k);
extern LIB3DSAPI void lib3ds_vector_cross(Lib3dsVector c, Lib3dsVector a, Lib3dsVector b);
extern LIB3DSAPI float lib3ds_vector_dot(Lib3dsVector a, Lib3dsVector b);
extern LIB3DSAPI float lib3ds_vector_squared(Lib3dsVector c);
extern LIB3DSAPI float lib3ds_vector_length(Lib3dsVector c);
extern LIB3DSAPI void lib3ds_vector_normalize(Lib3dsVector c);
extern LIB3DSAPI void lib3ds_vector_normal(Lib3dsVector n, Lib3dsVector a, Lib3dsVector b, Lib3dsVector c);
extern LIB3DSAPI void lib3ds_vector_cubic(Lib3dsVector c, Lib3dsVector a, Lib3dsVector p, Lib3dsVector q, Lib3dsVector b, float t);
extern LIB3DSAPI void lib3ds_vector_min(Lib3dsVector c, Lib3dsVector a);
extern LIB3DSAPI void lib3ds_vector_max(Lib3dsVector c, Lib3dsVector a);

/** @name Quaternions */
/** @{ */
extern LIB3DSAPI void lib3ds_quat_identity(Lib3dsQuat c);
extern LIB3DSAPI void lib3ds_quat_copy(Lib3dsQuat dest, Lib3dsQuat src);
extern LIB3DSAPI void lib3ds_quat_axis_angle(Lib3dsQuat c, Lib3dsVector axis, float angle);
extern LIB3DSAPI void lib3ds_quat_neg(Lib3dsQuat c);
extern LIB3DSAPI void lib3ds_quat_cnj(Lib3dsQuat c);
extern LIB3DSAPI void lib3ds_quat_mul(Lib3dsQuat c, Lib3dsQuat a, Lib3dsQuat b);
extern LIB3DSAPI void lib3ds_quat_scalar(Lib3dsQuat c, float k);
extern LIB3DSAPI void lib3ds_quat_normalize(Lib3dsQuat c);
extern LIB3DSAPI void lib3ds_quat_inv(Lib3dsQuat c);
extern LIB3DSAPI float lib3ds_quat_dot(Lib3dsQuat a, Lib3dsQuat b);
extern LIB3DSAPI float lib3ds_quat_squared(Lib3dsQuat c);
extern LIB3DSAPI float lib3ds_quat_length(Lib3dsQuat c);
extern LIB3DSAPI void lib3ds_quat_ln(Lib3dsQuat c);
extern LIB3DSAPI void lib3ds_quat_ln_dif(Lib3dsQuat c, Lib3dsQuat a, Lib3dsQuat b);
extern LIB3DSAPI void lib3ds_quat_exp(Lib3dsQuat c);
extern LIB3DSAPI void lib3ds_quat_slerp(Lib3dsQuat c, Lib3dsQuat a, Lib3dsQuat b, float t);
extern LIB3DSAPI void lib3ds_quat_squad(Lib3dsQuat c, Lib3dsQuat a, Lib3dsQuat p, Lib3dsQuat q, Lib3dsQuat b, float t);
extern LIB3DSAPI void lib3ds_quat_tangent(Lib3dsQuat c, Lib3dsQuat p, Lib3dsQuat q, Lib3dsQuat n);
/** @} */

/** @name Matrices */
/** @{ */
extern LIB3DSAPI void lib3ds_matrix_zero(Lib3dsMatrix m);
extern LIB3DSAPI void lib3ds_matrix_identity(Lib3dsMatrix m);
extern LIB3DSAPI void lib3ds_matrix_copy(Lib3dsMatrix dest, Lib3dsMatrix src);
extern LIB3DSAPI void lib3ds_matrix_neg(Lib3dsMatrix m);
extern LIB3DSAPI void lib3ds_matrix_abs(Lib3dsMatrix m);
extern LIB3DSAPI void lib3ds_matrix_transpose(Lib3dsMatrix m);
extern LIB3DSAPI void lib3ds_matrix_add(Lib3dsMatrix m, Lib3dsMatrix a, Lib3dsMatrix b);
extern LIB3DSAPI void lib3ds_matrix_sub(Lib3dsMatrix m, Lib3dsMatrix a, Lib3dsMatrix b);
extern LIB3DSAPI void lib3ds_matrix_mult(Lib3dsMatrix m, Lib3dsMatrix n);
extern LIB3DSAPI void lib3ds_matrix_scalar(Lib3dsMatrix m, float k);
extern LIB3DSAPI float lib3ds_matrix_det(Lib3dsMatrix m);
extern LIB3DSAPI void lib3ds_matrix_adjoint(Lib3dsMatrix m);
extern LIB3DSAPI Lib3dsBool lib3ds_matrix_inv(Lib3dsMatrix m);
extern LIB3DSAPI void lib3ds_matrix_translate_xyz(Lib3dsMatrix m, float x, float y, float z);
extern LIB3DSAPI void lib3ds_matrix_translate(Lib3dsMatrix m, Lib3dsVector t);
extern LIB3DSAPI void lib3ds_matrix_scale_xyz(Lib3dsMatrix m, float x, float y, float z);
extern LIB3DSAPI void lib3ds_matrix_scale(Lib3dsMatrix m, Lib3dsVector s);
extern LIB3DSAPI void lib3ds_matrix_rotate_x(Lib3dsMatrix m, float phi);
extern LIB3DSAPI void lib3ds_matrix_rotate_y(Lib3dsMatrix m, float phi);
extern LIB3DSAPI void lib3ds_matrix_rotate_z(Lib3dsMatrix m, float phi);
extern LIB3DSAPI void lib3ds_matrix_rotate(Lib3dsMatrix m, Lib3dsQuat q);
extern LIB3DSAPI void lib3ds_matrix_rotate_axis(Lib3dsMatrix m, Lib3dsVector axis, float angle);
extern LIB3DSAPI void lib3ds_matrix_camera(Lib3dsMatrix matrix, Lib3dsVector pos, Lib3dsVector tgt, float roll);
extern LIB3DSAPI void lib3ds_vector_transform(Lib3dsVector c, Lib3dsMatrix m, Lib3dsVector a);
/** @} */

/** @} */
/** @defgroup io IO Handling */
/** @{ */

extern LIB3DSAPI Lib3dsIo* lib3ds_io_new(void *self, Lib3dsIoSeekFunc seek_func, Lib3dsIoTellFunc tell_func,
                                         Lib3dsIoReadFunc read_func, Lib3dsIoWriteFunc write_func,
                                         Lib3dsIoLogFunc log_func);
extern LIB3DSAPI void lib3ds_io_free(Lib3dsIo *io);

/** @} */
/** @defgroup objects Materials, Cameras, Lights, Meshes */
/** @{ */


extern LIB3DSAPI Lib3dsMaterial* lib3ds_material_new();
extern LIB3DSAPI void lib3ds_material_free(Lib3dsMaterial *material);

extern LIB3DSAPI Lib3dsCamera* lib3ds_camera_new(const char *name);
extern LIB3DSAPI void lib3ds_camera_free(Lib3dsCamera *mesh);

extern LIB3DSAPI Lib3dsLight* lib3ds_light_new(const char *name);
extern LIB3DSAPI void lib3ds_light_free(Lib3dsLight *mesh);

extern LIB3DSAPI Lib3dsMesh* lib3ds_mesh_new(const char *name);
extern LIB3DSAPI void lib3ds_mesh_free(Lib3dsMesh *mesh);
extern LIB3DSAPI void lib3ds_mesh_alloc_vertices(Lib3dsMesh *mesh, Lib3dsWord nvertices);
extern LIB3DSAPI void lib3ds_mesh_alloc_flags(Lib3dsMesh *mesh, Lib3dsWord nflags);
extern LIB3DSAPI void lib3ds_mesh_alloc_texcos(Lib3dsMesh *mesh, Lib3dsWord ntexcos);
extern LIB3DSAPI void lib3ds_mesh_alloc_faces(Lib3dsMesh *mesh, Lib3dsWord nfaces);
extern LIB3DSAPI void lib3ds_mesh_bounding_box(Lib3dsMesh *mesh, Lib3dsVector bmin, Lib3dsVector bmax);
extern LIB3DSAPI void lib3ds_mesh_calculate_face_normals(Lib3dsMesh *mesh, Lib3dsVector *face_normals);
extern LIB3DSAPI void lib3ds_mesh_calculate_normals(Lib3dsMesh *mesh, Lib3dsVector *normalL);

/** @} */
/** @defgroup nodes Hierachy, Keyframing */
/** @{ */

extern LIB3DSAPI Lib3dsTrack* lib3ds_track_new(Lib3dsTrackType type, Lib3dsDword nkeys);
extern LIB3DSAPI void lib3ds_track_free(Lib3dsTrack *track);
extern LIB3DSAPI void lib3ds_track_resize(Lib3dsTrack *track, Lib3dsDword nkeys);
extern LIB3DSAPI void lib3ds_track_setup(Lib3dsTrack *track);
extern LIB3DSAPI void lib3ds_track_eval_bool(Lib3dsTrack *track, Lib3dsBool *value, float t);
extern LIB3DSAPI void lib3ds_track_eval_float(Lib3dsTrack *track, float *value, float t);
extern LIB3DSAPI void lib3ds_track_eval_vector(Lib3dsTrack *track, Lib3dsVector value, float t);
extern LIB3DSAPI void lib3ds_track_eval_quat(Lib3dsTrack *track, Lib3dsQuat value, float t);
extern LIB3DSAPI void lib3ds_track_eval_morph(Lib3dsTrack *track, char *name, float t);

extern LIB3DSAPI Lib3dsNode* lib3ds_node_new(Lib3dsNodeType type);
extern LIB3DSAPI void lib3ds_node_free(Lib3dsNode *node);
extern LIB3DSAPI void lib3ds_node_eval(Lib3dsNode *node, float t);
extern LIB3DSAPI Lib3dsNode* lib3ds_node_by_name(Lib3dsNode *node, const char* name, Lib3dsNodeType type);
extern LIB3DSAPI Lib3dsNode* lib3ds_node_by_id(Lib3dsNode *node, Lib3dsWord node_id);

/** @} */
/** @defgroup files Files */
/** @{ */

/*
    sdsd
    dsdsdssd
    dsdd
*/
extern LIB3DSAPI Lib3dsFile* lib3ds_file_load(
    const char *filename);

extern LIB3DSAPI Lib3dsBool lib3ds_file_save(Lib3dsFile *file, const char *filename);
extern LIB3DSAPI Lib3dsFile* lib3ds_file_new();
extern LIB3DSAPI void lib3ds_file_free(Lib3dsFile *file);
extern LIB3DSAPI void lib3ds_file_eval(Lib3dsFile *file, float t);
extern LIB3DSAPI Lib3dsBool lib3ds_file_read(Lib3dsFile *file, Lib3dsIo *io);
extern LIB3DSAPI Lib3dsBool lib3ds_file_write(Lib3dsFile *file, Lib3dsIo *io);
extern LIB3DSAPI void lib3ds_file_material_reserve(Lib3dsFile *file, Lib3dsIntd size, Lib3dsBool force);
extern LIB3DSAPI void lib3ds_file_material_insert(Lib3dsFile *file, Lib3dsMaterial *material, Lib3dsIntd index);
extern LIB3DSAPI void lib3ds_file_material_remove(Lib3dsFile *file, Lib3dsIntd index);
extern LIB3DSAPI Lib3dsIntd lib3ds_file_material_by_name(Lib3dsFile *file, const char *name);
extern LIB3DSAPI void lib3ds_file_camera_reserve(Lib3dsFile *file, Lib3dsIntd size, Lib3dsBool force);
extern LIB3DSAPI void lib3ds_file_camera_insert(Lib3dsFile *file, Lib3dsCamera *camera, Lib3dsIntd index);
extern LIB3DSAPI void lib3ds_file_camera_remove(Lib3dsFile *file, Lib3dsIntd index);
extern LIB3DSAPI Lib3dsIntd lib3ds_file_camera_by_name(Lib3dsFile *file, const char *name);
extern LIB3DSAPI void lib3ds_file_light_reserve(Lib3dsFile *file, Lib3dsIntd size, Lib3dsBool force);
extern LIB3DSAPI void lib3ds_file_light_insert(Lib3dsFile *file, Lib3dsLight *light, Lib3dsIntd index);
extern LIB3DSAPI void lib3ds_file_light_remove(Lib3dsFile *file, Lib3dsIntd index);
extern LIB3DSAPI Lib3dsIntd lib3ds_file_light_by_name(Lib3dsFile *file, const char *name);
extern LIB3DSAPI void lib3ds_file_mesh_reserve(Lib3dsFile *file, Lib3dsIntd size, Lib3dsBool force);
extern LIB3DSAPI void lib3ds_file_mesh_insert(Lib3dsFile *file, Lib3dsMesh *mesh, Lib3dsIntd index);
extern LIB3DSAPI void lib3ds_file_mesh_remove(Lib3dsFile *file, Lib3dsIntd index);
extern LIB3DSAPI Lib3dsIntd lib3ds_file_mesh_by_name(Lib3dsFile *file, const char *name);
extern LIB3DSAPI Lib3dsMesh* lib3ds_file_mesh_for_node(Lib3dsFile *file, Lib3dsNode *node);
extern LIB3DSAPI Lib3dsNode* lib3ds_file_node_by_name(Lib3dsFile *file, const char* name, Lib3dsNodeType type);
extern LIB3DSAPI Lib3dsNode* lib3ds_file_node_by_id(Lib3dsFile *file, Lib3dsWord node_id);
extern LIB3DSAPI void lib3ds_file_insert_node(Lib3dsFile *file, Lib3dsNode *node);
extern LIB3DSAPI void lib3ds_file_remove_node(Lib3dsFile *file, Lib3dsNode *node);
extern LIB3DSAPI void lib3ds_file_minmax_node_id(Lib3dsFile *file, Lib3dsWord *min_id, Lib3dsWord *max_id);
extern LIB3DSAPI void lib3ds_file_bounding_box_of_objects(Lib3dsFile *file, Lib3dsBool include_meshes, Lib3dsBool include_cameras, Lib3dsBool include_lights, Lib3dsVector bmin, Lib3dsVector bmax);
extern LIB3DSAPI void lib3ds_file_bounding_box_of_nodes(Lib3dsFile *file, Lib3dsBool include_meshes, Lib3dsBool include_cameras, Lib3dsBool include_lights, Lib3dsVector bmin, Lib3dsVector bmax, Lib3dsMatrix matrix);

/** @} */

#ifdef __cplusplus
}
#endif
#endif
