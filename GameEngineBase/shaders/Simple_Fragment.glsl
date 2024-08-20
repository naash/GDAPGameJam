
#version 430 core




smooth in vec4 ex_Position;
smooth in vec3 ex_Normal;			// Note Normal is a vec3
smooth in vec4 ex_Tex_UV;

out vec4 out_Color;		// If you don't say otherwise, this is the pixel colour


// Added to blend the textures 
uniform sampler2D texture1;




//For Edge Detection .................................................................................................
float threshold(in float thr1, in float thr2 , in float val) {
 if (val < thr1) {return 0.0;}
 if (val > thr2) {return 1.0;}
 return val;
}

// averaged pixel intensity from 3 color channels
float avg_intensity(in vec4 pix) {
 return (pix.r + pix.g + pix.b)/3.;
}

vec4 get_pixel(in vec2 coords, in float dx, in float dy) {
 return texture2D(texture1,coords + vec2(dx, dy));
}

// returns pixel color
float IsEdge(in vec2 coords){
  float dxtex = 1.0 / 900.0 /*image width*/;
  float dytex = 1.0 / 600.0 /*image height*/;
  float pix[9];
  int k = -1;
  float delta;

  // read neighboring pixel intensities
  for (int i=-1; i<2; i++) {
   for(int j=-1; j<2; j++) {
    k++;
    pix[k] = avg_intensity(get_pixel(coords,float(i)*dxtex,
                                          float(j)*dytex));
   }
  }

  // average color differences around neighboring pixels
  delta = (abs(pix[1]-pix[7])+
          abs(pix[5]-pix[3]) +
          abs(pix[0]-pix[8])+
          abs(pix[2]-pix[6])
           )/4.;

  return threshold(0.25,0.4,clamp(1.8*delta,0.0,1.0));
}
// Edge Detection Ends .................................................................................................


void main(void)
{

	
	 vec4 color = texture2D(texture1, ex_Tex_UV.st);

	//vec4 avgPixel = color;
	if(IsEdge(ex_Tex_UV.st) == 1.0)
	{
		color = vec4(0.0);
	}
		

	//vec2 pixelSize = vec2(1.0);
	//pixelSize.s = 1.0 / 1200.0 ;
	//pixelSize.t = 1.0 / 720.0 ;

	//vec2 pos = color.xy * pixelSize;
	

	//avgPixel += 1.0 * texture2D(texture1, vec2(pos.x - pixelSize.x , pos.y - pixelSize.y));
	//avgPixel += 2.0 * texture2D(texture1, vec2(pos.x , pos.y - pixelSize.y));
	//avgPixel += 1.0 * texture2D(texture1, vec2(pos.x + pixelSize.x , pos.y - pixelSize.y));
	//avgPixel += 2.0 * texture2D(texture1, vec2(pos.x - pixelSize.x , pos.y ));
	//avgPixel += 3.0 * texture2D(texture1, vec2(pos.x , pos.y));
	//avgPixel += 2.0 * texture2D(texture1, vec2(pos.x + pixelSize.x , pos.y ));
	//avgPixel += 1.0 * texture2D(texture1, vec2(pos.x - pixelSize.x , pos.y + pixelSize.y));
	//avgPixel += 2.0 * texture2D(texture1, vec2(pos.x  , pos.y + pixelSize.y));
	//avgPixel += 1.0 * texture2D(texture1, vec2(pos.x + pixelSize.x , pos.y + pixelSize.y));

	//avgPixel /= 15.0;


	//out_Color = texture2D(texture1, ex_Tex_UV.st);

	// Invisible Objects
	//if(color.r > 0.0)
	//	discard;



	out_Color = color;//vec4(color.rgb, 1.0);
}