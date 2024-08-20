#include "XmlUpdate.h"


XmlUpdate::XmlUpdate()
{
}


XmlUpdate::~XmlUpdate()
{
}
void XmlUpdate::CameraXmlUpdate()
{
	CVector3f tempEye;
	CVector3f tempTarget;
	CVector3f tempUp;

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(::_xmlFileName.c_str());

	pugi::xml_node camera = doc.child("ConfigSettings").child("Camera");


	for (pugi::xml_node_iterator it = camera.begin(); it != camera.end(); it++)
	{
		float eyex, eyey, eyez, upx, upy;

		eyex = ::g_pCamera->GetEye().x;
		eyey = ::g_pCamera->GetEye().y;
		eyez = ::g_pCamera->GetEye().z;
		upx = ::g_pCamera->GetPos().x;
		upy = ::g_pCamera->GetPos().y;
		for (pugi::xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ait++)
		{
			std::string temp;
			temp = ait->name();
			if (temp == "eyex")
				ait->set_value(eyex);
			if (temp == "eyey")
				ait->set_value(eyey);
			if (temp == "eyez")
				ait->set_value(eyez);
			if (temp == "upx")
				ait->set_value(upx);
			if (temp == "upy")
				ait->set_value(upy);
		}

	}
	doc.save_file(::_xmlFileName.c_str());
}

void XmlUpdate::SceneXmlUpdate()
{
	std::vector< CGameObject* > vec_pGameObjects;
	g_pFactoryMediator->getPhysicsObjects(vec_pGameObjects);

	int index = 0;
	pugi::xml_document doc;

	pugi::xml_parse_result result = doc.load_file(::_xmlFileName.c_str());

	pugi::xml_node scene = doc.child("ConfigSettings").child("Scene");

	for (pugi::xml_node_iterator it = scene.begin(); it != scene.end(); it++)
	{
		float rotx, roty, rotz;
		float posx, posy, posz;

		for (pugi::xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ait++)
		{
			rotx = vec_pGameObjects[index]->rotation.x;
			roty = vec_pGameObjects[index]->rotation.y;
			rotz = vec_pGameObjects[index]->rotation.z;
			posx = vec_pGameObjects[index]->position.x;
			posy = vec_pGameObjects[index]->position.y;
			posz = vec_pGameObjects[index]->position.z;

			std::string temp;
			temp = ait->name();

			if (temp == "rotx")
				ait->set_value(rotx);
			if (temp == "roty")
				ait->set_value(roty);
			if (temp == "rotz")
				ait->set_value(rotz);
			if (temp == "posx")
				ait->set_value(posx);
			if (temp == "posy")
				ait->set_value(posy);
			if (temp == "posz")
				ait->set_value(posz);

		}
		index++;

	}
	doc.save_file(::_xmlFileName.c_str());
}