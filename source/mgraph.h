//  mgraph.h
//
//  Created by Jeff Lubow on 1/13/23.
//

#ifndef mgraph_h
#define mgraph_h

#include "mgraph_cpp.h"

#define NUM_MAP_CHARS 40
#define OFFSET 50
#define SHAPE_DIVISOR 8
//#define MAX_NUM_SHAPES 12       //unimplemented

//#define NUM_FEATURES 14
#define NUM_FEATURES 8

#define FEATURE_ENERGY 0
#define FEATURE_ZCR 1
#define FEATURE_HFC 2
#define FEATURE_SPECIRR 3
#define FEATURE_SPECKURT 4
#define FEATURE_SPECCREST 5
#define FEATURE_SPECFLAT 6
#define FEATURE_SPECSKEW 7
//#define FEATURE_SPECCENTER 8
//#define FEATURE_SPECSPREAD 9
//#define FEATURE_SPECFLUX 10
//#define FEATURE_SPECDECR 11
//#define FEATURE_SPECSLOPE 12
//#define FEATURE_INHARM 13

//#define NUM_ACTIONS 7
#define NUM_ACTIONS 5

#define PARAM_XSCALE 0
#define PARAM_YSCALE 1
#define PARAM_SIZE 2
#define PARAM_YLOC 3
#define PARAM_BRIGHTNESS 4
//#define PARAM_ROTATION 5
//#define PARAM_XDEV 6

#define NUM_SHAPES 6
#define NUM_STYLES 3

#define MAX_MAPPINGS 24

typedef struct _morphograph {
    t_jbox l_box;
    //t_critical lock;
    t_jsvg *l_svg;
    t_symbol *l_shape;
    t_symbol *l_style;
    t_symbol *l_filepath;                //path for svg file and sample dir
    t_symbol *l_fnamesvg;                //name for svg file
    t_symbol *l_chosen_features[MAX_MAPPINGS];
    t_symbol *l_chosen_actions[MAX_MAPPINGS];
    
    long l_numlayers;                   //analysis status
    long l_mapcount;
    
    char *l_features[NUM_MAP_CHARS];
    char *l_actions[NUM_MAP_CHARS];
    char *l_shapes[NUM_MAP_CHARS];
    char *l_styles[NUM_MAP_CHARS];
    //double l_scalars[MAX_MAPPINGS];
    //t_atom *l_shapes[MAX_NUM_SHAPES];  //not yet; make a separate struct
    void *l_outlet_1;
    Parameters l_params;
    t_buffer_ref *l_buffer_reference;   //buffer ref
    //t_hashtab *hash_table;
} t_morphograph;

#endif /* mgraph_h */
