#include <string>
#include "sprite2d.h"
#include "scenegraph.h"

class INPUTGRAPH
{
private:
	SCENENODE * graphroot;
	SPRITE2D vslider;
	SPRITE2D hslider;
	SPRITE2D vball;
	SPRITE2D hball;
	float hwidth;
	float vheight;
	
	void SetVisible(bool newvis)
	{
		assert(graphroot);
		graphroot->SetChildVisibility(newvis);
	}
public:
	INPUTGRAPH() : graphroot(NULL) {}

	bool Init(SCENENODE & parentnode, const std::string & texturepath, std::ostream & error_output, const std::string & texsize)
	{
		float hheight, hball_scale, hx_pos, hy_pos;
		float vwidth, vx_pos, vy_pos;
		graphroot = &parentnode.AddNode();
		assert(graphroot);

		hwidth = 0.2;
		hheight = 0.2*1.33333;
		hx_pos = 0.5-hwidth/2;
		hy_pos = 0.8;
		hball_scale = 4.0;
		
		if(!hslider.Load(graphroot, texturepath+"/slider2.png", texsize, 1, error_output))
			return false;
		hslider.SetToBillboard(hx_pos, hy_pos, hwidth, hheight);
		if(!hball.Load(graphroot, texturepath+"/ball2.png", texsize, 2, error_output))
			return false;
		hball.SetToBillboard(hx_pos+hwidth/2-hwidth/(2.0*hball_scale), hy_pos+hheight/2-hheight/(2*hball_scale), hwidth/hball_scale, hheight/hball_scale);
		
		vwidth = hwidth/2;
		vheight = hheight/2;
		vx_pos = 0.35-vwidth/2;
		vy_pos = 0.87;
		if(!vslider.Load(graphroot, texturepath+"/accdec-slider.png", texsize, 1, error_output))
			return false;
		vslider.SetToBillboard(vx_pos, vy_pos, vwidth, vheight);
		if(!vball.Load(graphroot, texturepath+"/accdec-marker.png", texsize, 2, error_output))
			return false;
		vball.SetToBillboard(vx_pos, vy_pos, vwidth, vheight);
		return true;
	}
	
	void Update(const std::vector <float> & inputs)
	{
		const float throttle = inputs[CARINPUT::THROTTLE]-inputs[CARINPUT::BRAKE];
		float steer_value = inputs[CARINPUT::STEER_RIGHT];
		MATHVECTOR<float,3> translation;
		
		if (std::abs(inputs[CARINPUT::STEER_LEFT]) > std::abs(inputs[CARINPUT::STEER_RIGHT])) //use whichever control is larger
			steer_value = -inputs[CARINPUT::STEER_LEFT];
		
		translation = hball.GetTransform().GetTranslation();
		translation[0] = steer_value*hwidth/2.7;
		hball.GetTransform().SetTranslation(translation);
		translation = vball.GetTransform().GetTranslation();
		translation[1] = -throttle*vheight/2.7;
		vball.GetTransform().SetTranslation(translation);
	}
	
	void Hide()
	{
		SetVisible(false);
	}
	
	void Show()
	{
		SetVisible(true);
	}
};