//max ---------------------------------------------------------------------------------------------

#include "ext.h"                //core externals header
#include "ext_appendtohandle.h" //non-exported code from c74 - filewrite
#include "ext_dictobj.h"
#include "ext_buffer.h"
#include "jgraphics.h"          //JUCE-based drawing methods internal to the object

//morphograph -------------------------------------------------------------------------------------
#include "mgraph.h"
//#include "ext_critical.h"     //critical locks

//c++ ---------------------------------------------------------------------------------------------

#include "cella/features.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>
//#include <random>

//c -----------------------------------------------------------------------------------------------

extern "C" {

//c function prototypes

//essentials
void *morphograph_new(t_symbol *fn, short argc, t_atom *argv);
void morphograph_free(t_morphograph *x);
void morphograph_assist(t_morphograph *x, void *b, long m, long a, char *s);
    
//vanilla max basics
void morphograph_bang(t_morphograph *x);
void morphograph_anything(t_morphograph *x, const t_symbol * const s, const long ac, const t_atom *av);
void morphograph_dictionary(t_morphograph *x, t_symbol *s);

//custom max user methods
//void morphograph_mapping_table(t_morphograph *x, t_symbol *s, long argc, t_atom *argv);
//void morphograph_mapping_post(t_morphograph *x);
void morphograph_set(t_morphograph *x, t_symbol *s);
void morphograph_set_path(t_morphograph *x, t_symbol *s);
void morphograph_view(t_morphograph *x); //view buffer
void morphograph_size(t_morphograph *x, long width, long height); //ui size
void morphograph_load(t_morphograph *x, t_symbol *s);
void morphograph_process(t_morphograph *x);
void morphograph_writefile(t_morphograph *x, char *filename, short path);
void morphograph_dowrite(t_morphograph *x, t_symbol *s);
void morphograph_write(t_morphograph *x, t_symbol *s);

t_max_err morphograph_notify(t_morphograph *x, t_symbol *s, t_symbol *msg, void *sender, void *data); //buffer related

//custom/private user methods- internal only
static void post_info(void);
static void populate_features(t_morphograph *x);
static void populate_actions(t_morphograph *x);
static void populate_shapes(t_morphograph *x);
static void populate_styles(t_morphograph *x);
static void post_options(t_morphograph *x);
static void post_parameters(t_morphograph *x);
static void post_mappings(t_morphograph *x);
static void process_descmap(t_morphograph *x, t_dictionary *d);
static void process_transform(t_morphograph *x, t_dictionary *d);
static int get_feature_id(t_morphograph *x, short curr);
static int get_action_id(t_morphograph *x, short curr);

static void append_svg_open(t_morphograph *x);
//static void append_svg_txt(t_morphograph *x, char *line);
static void append_svg_txt(t_morphograph *x, std::string linestr);
static void append_svg_close(t_morphograph *x);

static t_class *morphograph_class;
static t_symbol *ps_dictionary;

t_symbol *ps_nothing; //allow for a non-msg (local to this object's code)

//global symbols
t_symbol *descmap, *transform, *shape, *layer, *filename, *style;

//-------------------------------------------------------------------------------------------------
//c++ class declarations / function prototypes ----------------------------------------------------
//-------------------------------------------------------------------------------------------------

class Morphograph;
class BufferInstance;
class ShapeWriter;

static void analyse_cpp(t_morphograph *x, Descriptors &d, BufferInstance *b);
static void mgraph_cpp(t_morphograph *x);

class ShapeWriter {
    t_morphograph *obj; //obj instead of x here
    Parameters *params;
    int vecsize;
    float elem_width, elem_height, x, y, xdev, linewidth, trilen, yoffset, size;
    unsigned int bright, rotation; //make x a double???
    unsigned short drawstyle;
    std::string linestr, bs, shape, xs, ys, ws, hs, xos, yos, lws;
    
    
private:
    ShapeWriter& operator = (ShapeWriter&);
    ShapeWriter(const ShapeWriter&);
    
public:
    
    ShapeWriter(t_morphograph *_obj, std::string &_shape) {
    //fork out primitive code to be the default, then stroke/fill
        obj = _obj;
        shape = _shape;
    
        //defaults
        size = 1.0;
        rotation = 0.;
        elem_width = 8.0;   //min width - should be attribute???
        elem_height = 8.0;  //min height - should be attribute???
        y = 0.5;
        xdev = 0.;
        bright = 0;
        linewidth = 0.5;
        drawstyle = 0; //0=stroke 1=fill 2=both
        
    }
    
    virtual ~ShapeWriter() {
	//linestr.delete(); //not sure if there is a better way...
        //clean up???
        //could be a memory leak here
    }
    
    void draw(){
        
        float baseline_scalar = 5;
        //default strings for filewriter
        float tx = (x / float(vecsize)) * float(params->width);
        float ty = y * params->height;

        float aw = elem_width + (baseline_scalar * size);   //actual width
        float hwn = -1. * (aw / 2.);    //half width negative
        float ah = elem_height + (baseline_scalar * size);  //actual height
        float hhn = -1. * (ah / 2.);    //half height negative
        
        ws = std::to_string(aw);
        std::string offset_x = std::to_string(hwn);
        hs = std::to_string(ah);
        std::string offset_y = std::to_string(hhn);
        xs = std::to_string(tx);
        ys = std::to_string(ty);
         
        lws = std::to_string(linewidth);
        bs = std::to_string(bright);
        
        // begin shape ------------------------------------------------
        linestr = "<"; //open
        
        if(shape == std::string("circles")){
            draw_circle();
        }
        if(shape == std::string("rectangles")){
            draw_rectangle();
        }
        if(shape == std::string("ellipses")){
            draw_ellipse();
        }
        if(shape == std::string("letters")){
            draw_letter();
        }
        if(shape == std::string("triangles")){
            //object_error((t_object *)x, "triangle is not implemented.");
            draw_triangle();
        }
        
        //this should be part of a group soon  <g><>...</g>
        switch(drawstyle){
            case 0: //stroke; consider stroke width
               	linestr.append("stroke=\"rgb(0,0,0)\" stroke-width=\"" + lws + "\" ");
                linestr.append("fill=\"transparent\" ");
                break;
            case 1: //fill
                linestr.append("fill=\"rgb(" + bs + "," + bs + "," + bs + ")\" ");
                break;
            case 2: //both
                linestr.append("stroke=\"rgb(0,0,0)\" stroke-width=\"0.2\" "); //should be [linewidth]
                linestr.append("fill=\"rgb(" + bs + "," + bs + "," + bs + ")\" ");
                break;
        }
        
        //transform characteristics
        std::string rstr = std::to_string(rotation);
        //std::string sc = std::to_string(size * 8.);
        
        linestr.append("transform=\""); //--------------------------
        linestr.append("translate(" + xs + " " + ys + ") ");
        //linestr.append("rotate(" + rstr + ", 50, 50) "); //2nd and 3rd args are in percentage
        linestr.append("rotate(" + rstr + ") ");
        linestr.append("translate(" + offset_x + " " + offset_y + ")");
        linestr.append("\""); //-------------------------------------
        
        // append linestring text to doc
        append_svg_txt(obj, linestr);
        
        // end shape ------------------------------------------------
        append_svg_txt(obj, "/>\n"); //close
        
        //lines should be brought back in via a max attribute
        /*
        // test lines -------------------------------------------------
        std::string tempwidth = std::to_string(params->width);
        std::string tempheight = std::to_string(params->height);
        
        linestr = "<line x1=\"" + xs + "\" ";
        linestr.append("y1=\"0\" ");
        //linestr.append("y1=\"" + tempheight);
        linestr.append("x2=\"" + xs + "\" ");
        //linestr.append("y2=\"0\" ");
        linestr.append("y2=\"" + tempheight + "\" ");
        linestr.append("stroke-width=\"" + ls + "\" stroke=\"black\"/>\n");
        append_svg_txt(obj, linestr);
         */

    }
    
    void set_params(Parameters *_params){
        params = _params;
    }
    void set_rotation(float _rot){
        rotation = unsigned(_rot) % 360;
    }
    void set_vecsize(long _vsize){
        vecsize = _vsize;
    }
    void set_width(float _wid){
        elem_width = _wid;
    }
    void set_height(float _height){
        elem_height = _height;
    }
    void set_size(float _size){
        size = _size;
    }
    void set_x(float _x){
        x = _x;
    }
    void set_y(float _y){
        y = _y;
    }
    void set_xdev(float _xdev){
        xdev = _xdev;
    }
    void set_linewidth(float _lwidth){
        linewidth = _lwidth;
    }
    /*
    void set_idx(unsigned _i){
        idx = _i;
    }*/
    void set_brightness(char _bright){
        bright = _bright;
    }
   
    void set_drawstyle(std::string _style){
        if(_style == std::string("stroke")){
            drawstyle = 0;
        }
        if(_style == std::string("fill")){
            drawstyle = 1;
        }
        if(_style == std::string("both")){
            drawstyle = 2;
        }
    }
    void set_drawlines(bool _t){
        
    }
    
private:

    void draw_triangle(){
    }
    
    void draw_circle(){
        //note that circles are drawn via their center point by default
        //linestr.append("circle cx=\"" + xs + "\" cy=\"" + ys + "\" r=\"0.5\" ");
        linestr.append("circle r=\"0.5\"");
    }

    void draw_rectangle(){
        //Rectangle(pPoint, width, height);
        linestr.append("rect width=\"" + ws + "\" height=\"" + hs + "\" " );
      //  linestr.append("rect x=\"" + xs + "\" y=\"" + ys + "\" width=\"" + ws + "\" height=\"" + hs + "\" ");
    }
    
    void draw_ellipse(){
        linestr.append("ellipse rx=\"" + ws + "\" ry=\"" + hs + "\" ");
        //linestr.append("ellipse ");
    }
    
    void draw_letter(){
        int l = rand() % 26;
        char ls = 'a';
   //     std::stringstream lss;
       //lss << (char)(ls + l);
        //std::cout << lss.str() << std::endl;
        switch(drawstyle){
            case 0://stroke
//                (*doc) << Text(
//                    pPoint(x / vecsize * params->width, y * params->height),
//                    lss.str(), Fill(),
//                    Font((size * params->height) / 16, "Verdana"),
//                    Stroke(linewidth, Color(0, 0, 0))
//                );
                break;
            case 1://fill
//                (*doc) << Text(
//                    pPoint(x / vecsize * params->width, y * params->height),
//                    lss.str(), Color(bright, bright, bright),
//                    Font((size * params->height) / 16, "Verdana")
//                );
                break;
            case 2://both
//                (*doc) << Text(
//                    pPoint(x / vecsize * params->width, y * params->height),
//                    lss.str(), Color(bright, bright, bright),
//                    Font((size * params->height) / 16, "Verdana"),
//                    Stroke(linewidth, Color(0, 0, 0))
//                );
                break;
            default:
//                (*doc) << Text(
//                    pPoint(x / vecsize * params->width, y * params->height),
//                    lss.str(), Color(bright, bright, bright),
//                    Font((size * params->height) / 16, "Verdana")
//                );
                break;
        }
    }
};

class Morphograph {
    
    t_morphograph *x;
    Parameters params;
    BufferInstance *bi;
    std::vector<Layer> layers;

private:
    
    Morphograph &operator = (Morphograph&);
    Morphograph(const Morphograph&);

public:
    
    //the x passed in here needs to be a different name than the one we use internally
    Morphograph (t_morphograph *_x, BufferInstance *_b) {

        x = _x;
        params = x->l_params;
        bi = _b;
    }
    
    virtual ~Morphograph () {
    }
    
    void add_layer (const std::string &shape) {
        Layer l;
        l.shape = shape;
        analyse_cpp(x, l.desc, bi);    //the contents of l.desc is implied because I'm not manipulating this struct currently
                                    //might want to populate this with the spectral features passed in via dictionary input
                                    //alternatively we can hold these values in a hash table and iterate through them to populate the descriptors
                                    //...seems like there should only be one copy of these.
        layers.push_back(l);
    }
    
    void render() {
        
        object_post((t_object *)x, "Rendering...");
        
        //write first lines for svg file into temp buf
        append_svg_open(x);
        
        //find the layer with the largest list for energy
        int max_frames = 0;
        for (unsigned i = 0; i < layers.size(); ++i) {
            if (max_frames < layers[i].desc.energy.size()) {
                max_frames = layers[i].desc.energy.size();
            }
        }
        
        double min_freq = params.sr / 2, max_freq = 1;  // large mins
        double min_irr = params.sr / 2, max_irr = 1;    // large mins
        double min_nrg = params.fft_size, max_nrg = 0;
        double min_zcr = params.sr / 2, max_zcr = 0;
        
        //resize the lists to all be standardized based on max_frames
        for (unsigned i = 0; i < layers.size (); ++i) {
            for (unsigned j = 0; j < layers[i].desc.energy.size (); ++j) {
                //layers[i].desc.highest_peak_Hz.resize (max_frames, 0);
                layers[i].desc.energy.resize(max_frames, 0);
                //layers[i].desc.zcr.resize (max_frames, 0);
            }
           
            min_freq = 0.;
            max_freq = params.sr / 2.;
            get_min_max (layers[i].desc.energy, min_nrg, max_nrg);
            get_min_max (layers[i].desc.zcr, min_zcr, max_zcr);
        }

        //draw all elements after calculating relevant data
        for (unsigned i = 0; i < layers.size(); ++i) {
            //how do we know that energy's size is the size of a vector???
            //need to look into this
            long vsize = layers[i].desc.energy.size();
            
            //j represents the analysis frame
            //why do we need to skip analysis frames?
            //this should be a parameter to thin the data out...
            unsigned skip_by = 2;
            
            for (unsigned j = 0; j < vsize; j += skip_by) {
                
                double sc_freq = (layers[i].desc.speccentr[j] / (max_freq - min_freq)) + min_freq;
                double sc_nrg = (layers[i].desc.energy[j] / (max_nrg - min_nrg)) + min_nrg;

                ShapeWriter swrite(x, layers[i].shape);
                
                                                
                for(int k = 0; k < x->l_mapcount; k++){
                    // j is the frame
                    double curr_feature_datum;
                    
                    switch(get_feature_id(x, k)){
                        case FEATURE_ENERGY: {
                            curr_feature_datum = layers[i].desc.energy[j];
                        } break;
                        case FEATURE_ZCR: {
                            curr_feature_datum = layers[i].desc.zcr[j];
                        } break;
                        case FEATURE_HFC: {
                            curr_feature_datum = layers[i].desc.hfc[j];
                        } break;
//                        case FEATURE_INHARM: {
//                            curr_feature_datum = layers[i].desc.inharmonicity[j];
//                        } break;
                        case FEATURE_SPECIRR: {
                            curr_feature_datum = layers[i].desc.specirr[j];
                        } break;
//                        case FEATURE_SPECCENTER: {
//                            curr_feature_datum = layers[i].desc.speccentr[j];
//                        } break;
//                        case FEATURE_SPECSPREAD: {
//                            curr_feature_datum = layers[i].desc.specspread[j];
//                        } break;
                        case FEATURE_SPECSKEW: {
                            curr_feature_datum = layers[i].desc.specskew[j];
                        } break;
                        case FEATURE_SPECKURT: {
                            curr_feature_datum = layers[i].desc.speckurt[j];
                        } break;
//                        case FEATURE_SPECFLUX: {
//                            curr_feature_datum = layers[i].desc.specflux[j];
//                        } break;
//                        case FEATURE_SPECDECR: {
//                            curr_feature_datum = layers[i].desc.specdecr[j];
//                        } break;
//                        case FEATURE_SPECSLOPE: {
//                            curr_feature_datum = layers[i].desc.specslope[j];
//                        } break;
                        case FEATURE_SPECFLAT: {
                            curr_feature_datum = layers[i].desc.specflat[j];
                        } break;
                        case FEATURE_SPECCREST: {
                            curr_feature_datum = layers[i].desc.speccrest[j];
                        } break;
                            
                        default: {
                            object_error((t_object *)x, "Render: Unknown or invalid feature id.  Aborting.");
                            return;
                        }
                    }
          
                    switch(get_action_id(x, k)){
                        case PARAM_ROTATION: {
                            //unimplemented
                            swrite.set_rotation(curr_feature_datum * 100.0);
                        } break;
                        case PARAM_XSCALE: {
                            //object_post((t_object *)x, "detected xscale");
                            swrite.set_width(curr_feature_datum);
                        } break;
                        case PARAM_YSCALE: {
                            //object_post((t_object *)x, "detected yscale");
                            swrite.set_height(curr_feature_datum);
                        } break;
                        case PARAM_SIZE: {
                            //object_post((t_object *)x, "detected size");
                            swrite.set_size(curr_feature_datum);
                        } break;
                        case PARAM_YLOC: {
                            //object_post((t_object *)x, "detected yloc; curr feature data: %f", curr_feature_datum);
                            
                            swrite.set_y(curr_feature_datum);
                        } break;
//                        case PARAM_XDEV: {
//                            //unimplemented
//                            object_error((t_object *)x, "x deviation is unimplemented.");
//                        } break;
                        case PARAM_BRIGHTNESS: {
                            
                            char b = curr_feature_datum * 255;
                            swrite.set_brightness(b);
                            //object_post((t_object *)x, "brightness %d", b);
                            
                        } break;
                        case PARAM_LINEWIDTH: {
                            //object_post((t_object *)x, "detected linewidth; curr feature data: %f", curr_feature_datum);
                            swrite.set_linewidth(curr_feature_datum * 2.5);
                        } break;
                        default: {
                            object_error((t_object *)x, "render: cannot find valid action id.");
                            return;
                        }
                    }
                }
                
                swrite.set_drawstyle(x->l_style->s_name);
                swrite.set_vecsize(vsize);
                //swrite.set_idx(j); //i is layer, j is analysis frame
                swrite.set_x(float(j));
                swrite.set_params(&params);
                swrite.draw();
        
            }
        }
        append_svg_close(x);
        //do something here to call write()
    }
    
private:
    
    void get_min_max (std::vector<double> &vals, double &min_v, double &max_v) {
        if (max<double> (&vals[0], vals.size()) > max_v) {
            max_v = max<double> (&vals[0], vals.size ());
        }
        if (min<double> (&vals[0], vals.size ()) < min_v) {
            min_v = min<double> (&vals[0], vals.size ());
        }
    }
};

//BufferInstance is a replacement class for WavFileIn
//specific to max
class BufferInstance {
    
    t_morphograph *x;
    t_buffer_info info;
    t_buffer_obj *obj;
    int dataRead;
    
public:
    BufferInstance(t_morphograph *_x) {
        x = _x;
        obj = buffer_ref_getobject(x->l_buffer_reference);
        buffer_getinfo(obj, &info);
        dataRead = 0;
    }
    
    ~BufferInstance() {
        //clean up
        //should I free the c++ buffer here ???
    }
    
    char * getFileName() {
        return buffer_getfilename(obj)->s_name;
    }
    //changed datatype in call to this
    long getNumChannels() {
        //return header.format.channel_number;
        return info.b_nchans;
    }
    
    //changed datatype in call to this
    float getSampleRate() {
        return info.b_sr;
    }
    
    //this was renamed from getDataSizeInBytes() and changed datatype ???
    long getDataSizeInFloats() {
        return info.b_size;
    }
    
    //is frames the same as samples ???
    long getNumSamples() {
        return info.b_frames;
        //buffer_getframecount(obj)  ???
    }
    
    //changed datatype in call to this
    long getLengthMS() {
        long numsamps = getNumSamples();
        long sr = (long)getSampleRate();
        return (1000 * numsamps / sr);
    }
};

//-------------------------------------------------------------------------------------------------
//C++/C functions
//-------------------------------------------------------------------------------------------------

static void analyse_cpp(t_morphograph *x, Descriptors &d, BufferInstance *b) {
    
    Parameters p = x->l_params;
    
    if ((double)b->getSampleRate() != p.sr) {
       
        object_error((t_object *)x, "%s invalid sampling rate in buffer's file %s: %8f vs params of object %8f.", b->getFileName(), b->getSampleRate(), p.sr);
       
        return;
    }
    
    long nsamps = b->getNumSamples();
    std::vector<double> vsamples(nsamps);
    
    if(buffer_ref_exists(x->l_buffer_reference)) {
        float *table = NULL;
        t_buffer_obj *obj = buffer_ref_getobject(x->l_buffer_reference);

        //read mono
        if (b->getNumChannels() == 1) {
            
            table = buffer_locksamples(obj);    //table is a pointer to the first sample
            std::copy(table, table + nsamps, vsamples.data());
            buffer_unlocksamples(obj);
            
            object_post((t_object *)x, "finished mono copy operation.  numsamples of analysis file: %d", nsamps);
        
        //read stereo
        } else if (b->getNumChannels() == 2) {
            
            std::vector<double> vstereo_samples (nsamps * 2);
            table = buffer_locksamples(obj);
            std::copy(table, table + nsamps, vstereo_samples.data());
            buffer_unlocksamples(obj);
            
            object_post((t_object *)x, "finished stereo copy operation.  numsamples of analysis file: %d.  st file was %d samples long", nsamps, nsamps * 2);
            
            for (unsigned i = 0; i < nsamps; ++i) {
                vsamples[i] = .5 * vstereo_samples[2 * i] + .5 * vstereo_samples[2 * i +1];
            }
                
        } else {
            
            //std::stringstream err;
            char *tmpstr = b->getFileName();
            //object_error((t_object *)x, "invalid number of channels in : %s.  Mono or stereo only.", tmpstr);
            object_error((t_object *)x, "invalid number of channels in : %s.  Mono only.", tmpstr);
            //err << "invalid number of channels in << " << tmpstr << "(mono or stereo only)";
            //err << "invalid number of channels in << " << tmpstr << "(mono only)";
           // throw std::runtime_error (err.str ());
            
        }
    }
    
    //generate window for analysis and populate requisite vars
    std::vector<double> vbuffer (p.fft_size * 2); // complex
    std::vector<double> window (p.fft_size);
    makeWindow<double> (&window[0], p.fft_size, .5, .5, 0); // hanning
    
    double winEnergy = 0;
    for (unsigned i = 0; i < p.fft_size; ++i) {
        winEnergy += window[i] * window[i];
    }
    
    std::vector<double> amps (p.fft_size / 2); // discard symmetry
    std::vector<double> freqs (p.fft_size / 2); // discard symmetry
    
    //find frequencies
    for (unsigned i = 0; i < p.fft_size / 2; ++i) {
        freqs[i] = p.sr / p.fft_size * i;
    }
        
    int ptr = 0;
    bool feature_valid = true;
    
    while (ptr < nsamps && feature_valid) {
        if (p.fft_size + ptr > nsamps) break; // discard incomplete frame

        //run fft()
        memset (&vbuffer[0], 0, sizeof (double) * 2 * p.fft_size);
        for (unsigned i = 0; i < p.fft_size; ++i) {
            vbuffer[2 * i] = window[i] * vsamples[i + ptr];
        }
        fft (&vbuffer[0], p.fft_size, -1);

        //find amplitudes
        for (unsigned i = 0; i < p.fft_size / 2; ++i) {
            double r = vbuffer[2 * i];
            double im = vbuffer[2 * i + 1];
            double a = sqrt (r * r + im * im);
            amps[i] = a;
        }
        
        int i;
        
        //default processes ---------------------------------------------------
        
        //energy
        double sum = 0;
        for (i = 0; i < (p.fft_size / 2); ++i) {
            double a = vsamples[i + ptr];
            sum += a * a;
        }
        double e = std::sqrt (sum / p.fft_size); //we push this later
        d.energy.push_back(e * 10.);
        //d.energy.push_back(e);
        
        //centroid
        double sc = speccentr(&amps[0], &freqs[0], p.fft_size / 2);
        d.speccentr.push_back(sc);
        
        //spectral spread
        double sspr = specspread(&amps[0], &freqs[0], p.fft_size / 2, sc);
        d.specspread.push_back(sspr);
        
        //end default processes -----------------------------------------------
        
        bool verbose = x->verbose;
        //iterate through the map list for features
        for(i = 0; i < x->l_mapcount; i++) {
            switch(get_feature_id(x, i)) {
                case FEATURE_ENERGY: {
                    if(verbose)
                        object_post((t_object *)x, "spec energy: %f", e * 10.);
                    //d.energy.push_back(e * 10.);
                } break;
                case FEATURE_ZCR: {
                    //double z = zcr<double>(&vsamples[ptr], p.fft_size / 2);
                    double z = zcr<double>(&vsamples[ptr], p.fft_size);
                    if(verbose)
                        object_post((t_object *)x, "spec zcr: %f", z * 10.);
                    d.zcr.push_back(z * 10.);
                } break;
                case FEATURE_HFC: {
                    double h = hfc(&amps[0], p.fft_size / 2);
                    if(verbose)
                        object_post((t_object *)x, "hfc: %f", h);
                    d.hfc.push_back(h);
                } break;
//                case FEATURE_INHARM: {
//                    //don't understand how to implement this
//                    //double ih = inharmonicity(&amps[0], &freqs[0], p.fft_size, <#T f0#>, <#T R#>, <#T &sumAmpl#>)
//                    object_error((t_object *)x, "inharmonicity is currently unimplemented.");
//                    feature_valid = false;
//                } break;
                case FEATURE_SPECIRR: {
                    double si = specirr(&amps[0], p.fft_size / 2);
                    if(verbose)
                        object_post((t_object *)x, "spec irr: %f", si * 0.001);
                    d.specirr.push_back(si * 0.001);
                } break;
//                case FEATURE_SPECCENTER: {
//                    //skip bc we already compute - should take this out
//                    object_post((t_object *)x, "spec centroid: %f", sc);
//                } break;
//                case FEATURE_SPECSPREAD:{
//                    //skip bc we already compute - should take this out
//                    object_post((t_object *)x, "spec spread: %f", sspr);
//                } break;
                case FEATURE_SPECSKEW: {
                    double ssk = specskew(&amps[0], &freqs[0], p.fft_size / 2, sc, sspr);
                    if(verbose)
                        object_post((t_object *)x, "spec skew: %f", ssk * 0.1);
                    d.specskew.push_back(ssk * 0.1);
                } break;
                case FEATURE_SPECKURT: {
                    double k = speckurt(&amps[0], &freqs[0], p.fft_size / 2, sc, sspr);
                    if(verbose)
                        object_post((t_object *)x, "spec kurt: %f", k);
                    d.speckurt.push_back(k * 0.01);
                } break;
//                case FEATURE_SPECFLUX: {
//                    //how to calculate the old amplitudes... ???
//                    //double f = specflux(&amps[0], oa, p.fft_size);
//                    object_error((t_object *)x, "spectral flux is currently unimplemented.");
//                    feature_valid = false;
//                } break;
//                case FEATURE_SPECDECR: {
//                    double sd = specdecr(&amps[0], p.fft_size / 2);
//                    object_post((t_object *)x, "spec decrease: %f", sd);
//                    d.specdecr.push_back(sd);
//                } break;
//                case FEATURE_SPECSLOPE: {
//                    double ssl = specslope(&amps[0], &freqs[0], p.fft_size / 2);
//                    object_post((t_object *)x, "spec slope: %f", ssl);
//                    d.specslope.push_back(ssl);
//                } break;
                case FEATURE_SPECFLAT: {
                    double sf = specflat(&amps[0], p.fft_size / 2);
                    if(verbose)
                        object_post((t_object *)x, "spec flatness: %f", sf * 10000.);
                    d.specflat.push_back(sf * 10000.);
                } break;
                case FEATURE_SPECCREST: {
                    double scr = speccrest(&amps[0], p.fft_size / 2);
                    if(verbose)
                        object_post((t_object *)x, "spec crest: %f", scr * 10);
                    d.speccrest.push_back(scr * 10);
                } break;
                    
                default: {
                    object_error((t_object *)x, "Analysis: input feature invalid; bailing.");
                    feature_valid = false;
                }
            }
        }
        
        ptr += p.hop_size;
    }
    return;
}

static int get_feature_id(t_morphograph *x, short curr) {
    char *current = x->l_chosen_features[curr]->s_name;
    
    for(int i = 0; i < NUM_FEATURES; i++) {
//        object_post((t_object *)x, "feature check. i: %d curr: %d", i, curr);
        if(strcmp(x->l_features[i], current) == 0){
            return i;
        }
    }
  //  object_post((t_object *)x, "returning -1");
    return -1;
}

static int get_action_id(t_morphograph *x, short curr) {
    char *current = x->l_chosen_actions[curr]->s_name;
    
    for(int i = 0; i < NUM_ACTIONS; i++) {
      //  object_post((t_object *)x, "feature check. i: %d curr: %d", i, curr);
        if(strcmp(x->l_actions[i], current) == 0){
            return i;
        }
    }
   // object_post((t_object *)x, "returning -1");

    return -1;
}

//run the cpp portion of the morphograph; assumes setup has completed
static void mgraph_cpp(t_morphograph *x) {

    std::string tshape = std::string(x->l_shape->s_name);
    
    try {
        srand (time (NULL)); //set the state of the random num gen
        
        BufferInstance b(x);
        Morphograph graph(x, &b);
        
        //THIS NEEDS TO CHANGE SOON ???
        //do not compute the analysis when you define the shape; shape is for rendering
        
        graph.add_layer(tshape);  //by default we'll only draw a single layer
        graph.render();
        
        //multiple layers using atom array
        //for(int i=0; i<x->l_numlayers; i++){
        //    graph.add_layer(atom_getsym(x->l_shapes[i])->s_name);
        //}
        
        object_post((t_object *)x, "///////// Finished processing /////////");
        outlet_bang(x->l_outlet_1);
    
        if(x->l_filepath && x->l_fnamesvg){
            
            t_symbol *fp;
            
            char full_file_path[strlen(x->l_filepath->s_name) + strlen(x->l_fnamesvg->s_name)];
            strcpy(full_file_path, x->l_filepath->s_name);
            strcat(full_file_path, x->l_fnamesvg->s_name);
            
            fp = gensym(full_file_path);
            
            morphograph_write(x, fp);
            morphograph_load(x, fp);
        }else{
            object_error((t_object *)x, "cannot load svg file; please check filepath/filename");
        }
        
    } catch (std::exception &e) {
        object_error((t_object *)x, "error calling morphograph: %s", e.what());
    } catch (...) {
        object_error((t_object *)x, "Fatal error calling morphograph: unknown exception");
    }

}

//c functions--------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//c functions: dict-related
//-------------------------------------------------------------------------------------------------

void morphograph_dictionary(t_morphograph *x, t_symbol *s){
    
    t_dictionary *d = dictobj_findregistered_retain(s);
    t_symbol *tfilename, *tshape, *tstyle;
    short criteria = 0;
    
    if(!d){  //throw error if dictionary cannot be found
        object_error((t_object *)x, "unable to reference dictionary named %s", s->s_name);
        return;
    }
    
    //filename to be written to disk as SVG file
    //maybe check to make sure about extension ???
    if(dictionary_hasentry(d, filename)){
        dictionary_getsym(d, filename, &tfilename);
        //object_post((t_object *)x, "dict in: filename: %s", tfilename->s_name);
        criteria++;
        x->l_fnamesvg = tfilename;
    }
        
    //process shape (only one currently)
    if(dictionary_hasentry(d, shape)){
        dictionary_getsym(d, shape, &tshape);
        //object_post((t_object *)x, "dict in: shape: %s", tshape->s_name);
        criteria++;
        x->l_shape = tshape;
    }
    
    if(dictionary_hasentry(d, style)){
        dictionary_getsym(d, style, &tstyle);
        //object_post((t_object *)x, "dict in: style: %s", tstyle->s_name);
        criteria++;
        x->l_style = tstyle;
    }
    
    if(dictionary_hasentry(d, descmap)){
        process_descmap(x, d);
        criteria++;
    }
     
    if(dictionary_hasentry(d, transform)){
        process_transform(x, d);
        criteria++;
    }
    
    if(criteria != 5){
        object_post((t_object *)x, "criteria not met!  Please check dictionary before processing morphograph.");
    }
    
    dictobj_release(d);
}

//there is a bug here - if the user specifies a feature that is not in the set it still takes
//but sets the value to 0 which is rotation, then errors as rotation is unimplemented; need to
//check what the user is doing against a valid set of options... ???
static void process_descmap(t_morphograph *x, t_dictionary *d){

    long numkeys, i = 0;
    
    t_symbol **desckeys = NULL;
    t_symbol *action;
    t_symbol *descriptor;
    
    t_max_err err = NULL;
    t_object *descmap_dictval = NULL;
    t_dictionary *dd = NULL;
        
    err = dictionary_getdictionary(d, descmap, &descmap_dictval);
    
    if(err){
        object_error((t_object *)x, "error processing descriptor mappings from dictionary...");
    }else{
        dd = (t_dictionary *)descmap_dictval;
        dictionary_getkeys(dd, &numkeys, &desckeys);

        x->l_mapcount = 0;
        for(i = 0; i < numkeys; i++){
            //get the key name
            descriptor = desckeys[i];
            //get the action associated with the key
            dictionary_getsym(dd, desckeys[i], (t_symbol **)&action);
            x->l_chosen_features[x->l_mapcount] = descriptor;
            x->l_chosen_actions[x->l_mapcount] = action;
            x->l_mapcount++;
            if(x->l_mapcount >= MAX_MAPPINGS){
                object_error((t_object *)x, "reached the maximum number of mappings.  aborting.");
                return;
            }
        }
        

        if(dd){
            dictionary_freekeys(dd, numkeys, desckeys);
        }
    }
}

//process transform and populate l_params for analysis
static void process_transform(t_morphograph *x, t_dictionary *d){
   // if(x->analyzed){
    t_object *transform_dictval = NULL;
    t_dictionary *td = NULL;
    t_max_err err = NULL;
    
    err = dictionary_getdictionary(d, transform, &transform_dictval);

    if(err){
        object_error((t_object *)x, "error processing transform info from dictionary...", err);
    }else{
        td = (t_dictionary *)transform_dictval;
        t_symbol *wid = gensym("width");
        t_symbol *hei = gensym("height");
        t_symbol *zoo = gensym("zoom");
        
        if(dictionary_hasentry(td, wid)){
            t_atom_long wv = NULL;
            dictionary_getlong(td, wid, &wv);
            x->l_params.width = (int)wv;
        }
        if(dictionary_hasentry(td, hei)){
            t_atom_long hv = NULL;
            dictionary_getlong(td, hei, &hv);
            x->l_params.height = (int)hv;
        }
        if(dictionary_hasentry(td, zoo)){
            t_atom_long z = NULL;
            dictionary_getlong(td, zoo, &z);
            x->l_params.zoom = (int)z;
        }
    }
}

//-------------------------------------------------------------------------------------------------
//c functions: main features
//-------------------------------------------------------------------------------------------------

static void populate_features(t_morphograph *x){
    x->l_features[0] = (char *)"energy";
    x->l_features[1] = (char *)"zcr";
    x->l_features[2] = (char *)"hfc";
    x->l_features[3] = (char *)"specirr";
    x->l_features[4] = (char *)"speckurt";
    x->l_features[5] = (char *)"speccrest";
    x->l_features[6] = (char *)"specflat";
    x->l_features[7] = (char *)"specskew";

//    x->l_features[8] = (char *)"speccentr";
//    x->l_features[9] = (char *)"specspread";
//    x->l_features[10] = (char *)"specflux";
//    x->l_features[11] = (char *)"specdecr";
//    x->l_features[12] = (char *)"specslope";
//    x->l_features[13] = (char *)"inharmonicity";
}

static void populate_actions(t_morphograph *x){
    
    x->l_actions[0] = (char *)"xscale";
    x->l_actions[1] = (char *)"yscale";
    x->l_actions[2] = (char *)"size";
    x->l_actions[3] = (char *)"ylocation";
    x->l_actions[4] = (char *)"brightness";
    x->l_actions[5] = (char *)"rotation";
    x->l_actions[6] = (char *)"linewidth";
//    x->l_actions[6] = (char *)"xdeviation";
    
}

static void populate_shapes(t_morphograph *x){
    x->l_shapes[0] = (char *)"circles";
    x->l_shapes[1] = (char *)"ellipses";
    x->l_shapes[2] = (char *)"rectangles";
    x->l_shapes[3] = (char *)"lines";
    x->l_shapes[4] = (char *)"letters";
    x->l_shapes[5] = (char *)"triangles";
}

static void populate_styles(t_morphograph *x){
    x->l_styles[0] = (char *)"stroke";
    x->l_styles[1] = (char *)"fill";
    x->l_styles[2] = (char *)"both";
}

//only called in class definition
static void post_info(void){
    post("[morphograph, ver. 0.2]");
    post("sound scores; inspired by Linda Bouchard");
    post("(c) 2022, Carmine Cella & Jeff Lubow");
}

static void post_options(t_morphograph *x){
    short i;
    
    object_post((t_object *)x, "///////// Shapes /////////");
    
    for(i = 0; i < NUM_SHAPES; i++){
        object_post((t_object *)x, "shape %d: %s", i, x->l_shapes[i]);
    }

    object_post((t_object *)x, "///////// Spectral Featurelist /////////");

    for(i = 0; i < NUM_FEATURES; i++){
        object_post((t_object *)x, "feature %d: %s", i, x->l_features[i]);
    }
    
    object_post((t_object *)x, "///////// Shape Actions /////////");
    
    for(i = 0; i < NUM_ACTIONS; i++){
        object_post((t_object *)x, "action %d: %s", i, x->l_actions[i]);
    }
    
    object_post((t_object *)x, "///////// Draw Styles /////////");
    
    for(i = 0; i < NUM_STYLES; i++){
        object_post((t_object *)x, "style %d: %s", i, x->l_styles[i]);
    }
    
}

static void post_mappings(t_morphograph *x){
    short i;
    if(x->l_mapcount == 0){
        object_post((t_object *)x, "No mappings defined currently.");
        return;
    }
    
    object_post((t_object *)x, "///////// Mappings /////////");

    for(i = 0; i < x->l_mapcount; i++){
        object_post((t_object *)x, "mapping id-%d -> feature %s mapped to %s", i, x->l_chosen_features[i]->s_name, x->l_chosen_actions[i]->s_name);
    }
   
}

static void post_parameters(t_morphograph *x){
    object_post((t_object *)x, "///////// Analysis / SVG parameters /////////");
    object_post((t_object *)x, "sample rate: %f", x->l_params.sr);
    object_post((t_object *)x, "fft size: %d", x->l_params.fft_size);
    object_post((t_object *)x, "hop size: %d", x->l_params.hop_size);
    object_post((t_object *)x, "width: %d", x->l_params.width);
    object_post((t_object *)x, "height: %d", x->l_params.height);
    object_post((t_object *)x, "zoom: %d", x->l_params.zoom);
}

void morphograph_process(t_morphograph *x) {
    //only process if a valid buffer name exists in the dictionary
    if(!buffer_ref_exists(x->l_buffer_reference)){
        object_error((t_object *)x, "No buffer reference! Cannot complete descriptor mapping, aborting analysis.");
        return;
    }
    
    if(!x->l_filepath){
        object_error((t_object *)x, "No valid filepath! Cannot complete file writing, aborting analysis.");
        return;
    }
    
    if(!x->l_fnamesvg){
        object_error((t_object *)x, "No valid filename, which may also indicate that a mapping dictionary hasn't been sent.  Aborting.");
        return;
    }
 
    object_post((t_object *)x, "Processing morphograph...");
    //maybe instead of calling this here, we could give this function an arg for the dictionary
    //to use to parse shapelayer mapping definitions... it could go above dictionary_getkeys()
    mgraph_cpp(x);

}

void morphograph_set(t_morphograph *x, t_symbol *s) {
    t_max_err err;
    
    if(!x->l_buffer_reference) {
        x->l_buffer_reference = buffer_ref_new((t_object *)x, s);
    } else {
        buffer_ref_set(x->l_buffer_reference, s);
    }
    
    //consider getting all buffer info here and populating object struct,
    //and/or calling translate_bufdata()
    //optionally use bang() for this
}

void morphograph_set_path(t_morphograph *x, t_symbol *s) {
    x->l_filepath = s;
    object_post((t_object *)x, "SVG write path: %s", x->l_filepath->s_name);
}

//this should be handled by the process_descmap() function
//void morphograph_mapping_table(t_morphograph *x, short argc, t_atom *argv);
//void myobject_message(t_myobject *x, t_symbol *s, long argc, t_atom *argv);
/*
void morphograph_mapping_table(t_morphograph *x, t_symbol *s, long argc, t_atom *argv){
    long i;
    //long max_mappings = MAX_MAPPINGS;
    
    t_atom *ap = argv;
    
    if(!x->hash_table){
        object_error((t_object *)x, "cannot locate valid hash table. Aborting.");
        return;
    }
    if(argc % 2 == 0){
        
        object_post((t_object *)x, "mapping table: received %d args. Processing %d pairs...", argc, argc / 2);
        hashtab_clear(x->hash_table);
        
        for(i = 0; i < argc; i++){
            if(atom_gettype(ap+i) == A_SYM && atom_gettype(ap+i+1) == A_SYM){
                hashtab_storesym(x->hash_table, atom_getsym(ap+i), atom_getsym(ap+i+1));
                i++; //0, 2, 4, etc.
            } else {
                object_error((t_object *)x, "mapping table: arguments are not all symbols!  Please try again.");
                return;
            }
        }
    } else {
        object_error((t_object *)x, "mapping table: wrong number of arguments!  Must be a multiple of two.");
        return;
    }
}
*/

/*
void morphograph_mapping_post(t_morphograph *x){
        object_post((t_object *)x, "mapping post: begin-------------------------------");
        //hashtab_print(x->hash_table);
        //object_post((t_object *)x, "--------------------------------------------------");
    
        long numkeys = 0;
        t_symbol **keys = NULL; //all keys
        t_symbol *symval = NULL;
        //t_max_err err;
        long i;


        hashtab_getkeys(x->hash_table, &numkeys, &keys);

        object_post((t_object *)x, "number of keys: %d", numkeys);

        for(i=0; i<numkeys; i++){
            //hashtab_lookup(x->hash_table, keys[i], &item);
            hashtab_lookup(x->hash_table, keys[i], (t_object **)&symval);
            
            //t_max_err hashtab_lookupsym(t_hashtab *x, t_symbol *key, t_symbol **val);
            //hashtab_lookupsym(x->hash_table, keys[i], (t_symbol **)&item);
            
            object_post((t_object *)x, "mapping_post-> item: %d / key: %s / value: %s", i, keys[i]->s_name, symval->s_name);
        }

        if(keys){
            object_post((t_object *)x, "mapping post: cleaning up...");
            sysmem_freeptr(keys);
        }
}
*/

//need this for buffer notification
t_max_err morphograph_notify(t_morphograph *x, t_symbol *s, t_symbol *msg, void *sender, void *data) {
    return buffer_ref_notify(x->l_buffer_reference, s, msg, sender, data);
}

//view buffer
void morphograph_view(t_morphograph *x) {
    if(buffer_ref_exists(x->l_buffer_reference)) {
        buffer_view(buffer_ref_getobject(x->l_buffer_reference));
    } else {
        object_error((t_object *)x, "no valid buffer reference");
    }
}

//-------------------------------------------------------------------------------------------------
//c functions:  graphics
//-------------------------------------------------------------------------------------------------

//load svg file from disk
void morphograph_load(t_morphograph *x, t_symbol *s){
    char        filename[MAX_PATH_CHARS];
    short       pathid = 0;
    t_fourcc    *type = NULL;
    t_fourcc    outtype;
    long        ntype = 0;

    
   // if (s == _sym_emptytext) {
    if (s == gensym("")) {
        //no path given by user
        if (open_dialog(filename, &pathid, &outtype, type, ntype)){
            return;
        }
    } else {
        //path is input by user (via open dialog object for ex)
        strcpy(filename,s->s_name);
        if (!locatefile_extended(filename, &pathid, &outtype, type, ntype)) {
            //continue
        } else {
            return;
        }
    }

    if (filename && filename[0]) {
        long len;
        len = strlen(filename);
        if ((len > 4) && (strcmp_case_insensitive(filename+len-4, ".svg") == 0)) {
            // if it ends in .svg we try to load an svg file
            t_jsvg *svg;
            svg = jsvg_create_from_file(filename, pathid);
            
            if (svg) {
                if (x->l_svg) {
                    jsvg_destroy(x->l_svg);
                }
                x->l_svg = svg;
                jbox_redraw(&x->l_box);
            }
        } else {
            object_error((t_object *)x, "cannot load svg file.  Please try something else.");
        }
    }
}

void morphograph_size(t_morphograph *x, long width, long height) {
    t_size size;
    size.width = (double) width;
    size.height = (double) height;
    jbox_set_size((t_object *) x, &size);
}

void morphograph_paint(t_morphograph *x, t_object *patcherview) {
    t_rect rect; //helper to gain info about patcherview
    jbox_get_rect_for_view((t_object *)x, patcherview, &rect);
    t_jgraphics *g = (t_jgraphics *)patcherview_get_jgraphics(patcherview);     // Get the graphics context.

    if(x && x->l_svg){
        t_rect newrect;
        
        double sw, sh;
    
        jgraphics_scale(g, rect.width, rect.height);
        //jgraphics_set_line_width(g, .04);
        jsvg_get_size(x->l_svg, &sw, &sh);
        jgraphics_scale(g, 1./sw, 1./sh);

//        newrect.x = rect.x;
//        newrect.y = rect.y;
//        newrect.width = sw;
//        newrect.height = sh;
//        jbox_set_rect_for_view((t_object *)x, patcherview, &newrect);
        
        jsvg_render(x->l_svg, g);
        
    }else{
        t_jrgba color_bg, color_rr;
        double offset = 2.;
        double offset2 = 7.;

        //alpha is transparent if zero
        color_bg.red = 0.064286; color_bg.green = 0.315738; color_bg.blue = 0.364286; color_bg.alpha = 1.;
        color_rr.red = 0.217857; color_rr.green = 0.492961; color_rr.blue = 0.496429; color_rr.alpha = 1.;

        
        
        jgraphics_set_source_jrgba(g, &color_bg);
        jgraphics_rectangle(g, 0, 0, rect.width, rect.height);
        jgraphics_fill(g);

        jgraphics_set_source_jrgba(g, &color_rr);
        jgraphics_rectangle_rounded(g, offset2, offset2, rect.width - offset2*2, rect.height - offset2*2, 30, 30);
        jgraphics_fill(g);
    }


}



//-------------------------------------------------------------------------------------------------
//c functions: std max api
//-------------------------------------------------------------------------------------------------

//new filewriter --------------------------------------------
//------------------------------------------------------------

void append_svg_open(t_morphograph *x){
    //initialize handle for svg filewriter
    x->l_svgh = sysmem_newhandle(0);

    //needs to grab dims from struct parameters
    char *root = (char *)"<svg version=\"1.1\" width=\"600\" height=\"400\" xmlns=\"http://www.w3.org/2000/svg\">\n";
    my_sysmem_appendtextptrtohand(root, x->l_svgh);
}

//void append_svg_txt(t_morphograph *x, char *line){
void append_svg_txt(t_morphograph *x, std::string linestr){
    long linelen = linestr.length() + 1;
    char line[linelen];
    
    strcpy(line, linestr.c_str());
    my_sysmem_appendtextptrtohand(line, x->l_svgh);
    memset(line, '\0', sizeof(char) * linelen); //this ok???
}

void append_svg_close(t_morphograph *x){
    char *close = (char *)"</svg>";
    my_sysmem_appendtextptrtohand(close, x->l_svgh);
}

void morphograph_write(t_morphograph *x, t_symbol *s){
    //need this to avoid threading conflicts
    defer(x, (method)morphograph_dowrite, s, 0, NULL);
}

void morphograph_dowrite(t_morphograph *x, t_symbol *s){
    char filename[512];
    short pathid;
    t_fourcc type = NULL;
    t_fourcc otype;
    
    if (s == gensym("")) { // if no arg, ask for file
        if (saveasdialog_extended(filename, &pathid, &otype, &type, 1))     // non-zero: user cancelled
            return;
    } else {
        strcpy(filename, s->s_name);
        pathid = path_getdefault();
    }
    morphograph_writefile(x, filename, pathid);
}

void morphograph_writefile(t_morphograph *x, char *filename, short path){
    //check to see if text buffer handle exists
    if(x->l_svgh != NULL){
        long err;
        t_filehandle fh;
            
        //create file
        err = path_createsysfile(filename, path, 'TEXT', &fh);
        if (err)
            return;
        //write file
        err = sysfile_writetextfile(fh, x->l_svgh, TEXT_LB_NATIVE);
        sysfile_close(fh);
    }else{
        object_error((t_object *)x, "cannot write file - svg buffer is not properly initialized.");
    }
}

//----------------------------------------------------------------

//does nothing atm
void morphograph_anything(t_morphograph *x, const t_symbol * const s, const long ac, const t_atom *av){
    
}

void morphograph_bang(t_morphograph *x){
    post_parameters(x);
    post_options(x);
    post_mappings(x);
}

void morphograph_free(t_morphograph *x) {
    //critical_free(x->lock);

    object_free(x->l_buffer_reference);
    jbox_free((t_jbox *)x);
    
    if (x->l_svg) {
        jsvg_destroy(x->l_svg);
        x->l_svg = NULL;
    }
    //hashtab_chuck(x->hash_table);
}

void morphograph_assist(t_morphograph *x, void *b, long m, long a, char *s) {
    // this system eliminates the need for a STR# resource
    if (m==1) {
        switch (a) {
            case 0: sprintf(s,"assistance inlet 0"); break;
            case 1: sprintf(s,"assistance inlet 1"); break; //if it exists
        }
    }
    else if (m==2) {
        switch (a) {
        case 0: sprintf(s,"File Data Output"); break;
        case 1: sprintf(s,"bang On End of File"); break;
        }
    }
}

void *morphograph_new(t_symbol *msg, short argc, t_atom *argv) {
    t_morphograph *x;
    t_dictionary *d;
    long boxflags;
    //long attrstart = attr_args_offset(argc, argv);
    
    if (!(d=object_dictionaryarg(argc,argv)))
        return NULL;
    
    x = (t_morphograph *)object_alloc(morphograph_class);
    
    if(x){
        boxflags = 0
                | JBOX_DRAWFIRSTIN
                //  | JBOX_NODRAWBOX
                //  | JBOX_DRAWINLAST
                | JBOX_TRANSPARENT
                //  | JBOX_NOGROW
                //  | JBOX_GROWY
                | JBOX_GROWBOTH
                //  | JBOX_IGNORELOCKCLICK
                | JBOX_HILITE
                | JBOX_BACKGROUND
                //  | JBOX_NOFLOATINSPECTOR
                //  | JBOX_TEXTFIELD
                ;
        
        jbox_new(&x->l_box, boxflags, argc, argv);
        x->l_box.b_firstin = (t_object *)x;
        
        //x->outlet_dict = outlet_new(x, "dictionary");
        x->l_outlet_1 = bangout((t_object *)x);
        
        x->l_numlayers = 0;
        x->l_mapcount = 0;
        x->l_filepath = NULL;
        x->l_fnamesvg = NULL;
        x->l_buffer_reference = NULL;
        x->verbose = false;
    
        x->l_shape = NULL;
        x->l_svg = NULL;
        x->l_svgh = NULL;
        //x->hash_table = (t_hashtab *)hashtab_new(0);
        
        //fill UI option arrays for max window
        populate_features(x);
        populate_actions(x);
        populate_shapes(x);
        populate_styles(x);
                
        x->l_params.sr = 44100.0;
        x->l_params.fft_size = 4096;
        x->l_params.hop_size = 512;
        x->l_params.width = 100;
        x->l_params.height = 100;
        x->l_params.zoom = 3;
        
        //globals
        descmap = gensym("descmap");
        transform = gensym("transform");
        shape = gensym("shape");
        layer = gensym("layer");
        filename = gensym("filename");
        style = gensym("style");
        
        attr_dictionary_process(x,d);
        jbox_ready(&x->l_box);
        
        
        
//        if(attrstart){
//            object_attr_setvalueof(x, gensym("keys"), attrstart, argv);
//        }
        attr_args_process(x, argc, argv);
        
    }

    return x;
}

void ext_main(void *r) {
    
    t_class *c;
    ps_nothing = gensym("");
    c = class_new("morphograph", (method)morphograph_new, (method)morphograph_free, sizeof(t_morphograph), (method)NULL, A_GIMME, 0);
    c->c_flags |= CLASS_FLAG_NEWDICTIONARY;
    
    jbox_initclass(c, 0);
    
    //max basics
    class_addmethod(c, (method)morphograph_anything, "anything", A_GIMME, 0);
    class_addmethod(c, (method)morphograph_bang, "bang", 0);
	class_addmethod(c, (method)morphograph_assist,	"assist", A_CANT, 0);
    //test text stuff
    class_addmethod(c, (method)morphograph_write, "write", A_DEFSYM, 0);
    
    //register custom user methods
    class_addmethod(c, (method)morphograph_set, "set", A_SYM, 0);
    class_addmethod(c, (method)morphograph_size, "size", A_LONG, A_LONG, 0);
    class_addmethod(c, (method)morphograph_set_path, "set_path", A_SYM, 0);
    class_addmethod(c, (method)morphograph_dictionary, "dictionary", A_SYM, 0);
    class_addmethod(c, (method)morphograph_load, "load", A_DEFSYM, 0); //default sym; empty string???
    class_addmethod(c, (method)morphograph_process, "process", 0);

    //class_addmethod(c, (method)morphograph_mapping_table, "mapping_table", A_GIMME, 0); //hashtable experiment
    //class_addmethod(c, (method)morphograph_mapping_post, "mapping_post", 0);

    //max internals methods
    class_addmethod(c, (method)morphograph_notify, "notify", A_CANT, 0);
    class_addmethod(c, (method)morphograph_assist, "assist", A_CANT, 0);
    class_addmethod(c, (method)morphograph_view, "view", 0);
    class_addmethod(c, (method)morphograph_paint, "paint", A_CANT, 0);
    
    //misc attributes
    
    CLASS_ATTR_CHAR(c, "verbose", 0, t_morphograph, verbose);
    CLASS_ATTR_STYLE(c, "verbose", 0, "onoff");
    CLASS_ATTR_LABEL(c, "verbose", 0, "Verbose Mode");
    CLASS_ATTR_DEFAULTNAME_SAVE(c, "verbose", 0, "0");
    
    //morphograph specific attr declarations
    
    CLASS_STICKY_ATTR(c, "category", 0, "Analysis");
    
    CLASS_ATTR_DOUBLE(c, "p_samplerate", 0, t_morphograph, l_params.sr);
    CLASS_ATTR_LABEL(c, "p_samplerate", 0, "Analysis Sample Rate");
    //CLASS_ATTR_ORDER(c, "p_samplerate", 0, "1");
    CLASS_ATTR_DEFAULTNAME_SAVE(c, "p_samplerate", 0, "44100.0");
    
    CLASS_ATTR_LONG(c, "p_fftsize", 0, t_morphograph, l_params.fft_size);
    CLASS_ATTR_LABEL(c, "p_fftsize", 0, "Analysis FFT Size");
    //CLASS_ATTR_ORDER(c, "p_fftsize", 0, "2");
    CLASS_ATTR_DEFAULTNAME_SAVE(c, "p_fftsize", 0, "4096");
    
    CLASS_ATTR_LONG(c, "p_hopsize", 0, t_morphograph, l_params.hop_size);
    CLASS_ATTR_LABEL(c, "p_hopsize", 0, "Analysis Hop Size");
    //CLASS_ATTR_ORDER(c, "p_hopsize", 0, "3");
    CLASS_ATTR_DEFAULTNAME_SAVE(c, "p_hopsize", 0, "512");

    CLASS_STICKY_ATTR(c, "category", 0, "SVG output");

    CLASS_ATTR_LONG(c, "p_width", 0, t_morphograph, l_params.width);
    CLASS_ATTR_LABEL(c, "p_width", 0, "SVG width in pixels");
    //CLASS_ATTR_ORDER(c, "p_hopsize", 0, "3");
    CLASS_ATTR_DEFAULTNAME_SAVE(c, "p_hopsize", 0, "512");
    
    CLASS_ATTR_LONG(c, "p_height", 0, t_morphograph, l_params.height);
    CLASS_ATTR_LABEL(c, "p_height", 0, "SVG height in pixels");
    //CLASS_ATTR_ORDER(c, "p_hopsize", 0, "3");
    CLASS_ATTR_DEFAULTNAME_SAVE(c, "p_hopsize", 0, "512");

    CLASS_ATTR_LONG(c, "p_zoom", 0, t_morphograph, l_params.zoom);
    CLASS_ATTR_LABEL(c, "p_zoom", 0, "SVG zoom factor");
    //CLASS_ATTR_ORDER(c, "p_hopsize", 0, "3");
    CLASS_ATTR_DEFAULTNAME_SAVE(c, "p_hopsize", 0, "512");

    
    CLASS_STICKY_ATTR_CLEAR(c, "category");

    CLASS_ATTR_DEFAULT(c,"patching_rect",0, "0. 0. 80. 80.");
    CLASS_ATTR_DEFAULT(c, "rect", 0, "0. 0. 50. 50.");  //for UI

    class_register(CLASS_BOX, c);
	morphograph_class = c;

    ps_dictionary = gensym("dictionary");  //small optimization to bypass symbol table; otherwise we'd need to generate this symbol every time
    
    post_info();
}

} // extern "C"
