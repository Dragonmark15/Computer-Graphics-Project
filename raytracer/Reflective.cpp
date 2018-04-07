#include "Reflective.h"
#include "Scene.h"

Reflective::Reflective(Scene* inputScenePtr) { 
	scenePtr = inputScenePtr;
	type = "Mirror";
	ambient = 0.1;
}
Reflective::Reflective(Scene* inputScenePtr, Vector3D inputReflectColor) {
	scenePtr = inputScenePtr;
	reflectColor = inputReflectColor;
	type = "Glaze";
	ambient = 0.1;
}
Reflective::Reflective(Scene* inputScenePtr, Vector3D inputReflectColor, float inputAmbient) {
	scenePtr = inputScenePtr;
	reflectColor = inputReflectColor;
	type = "Glaze";
	ambient = inputAmbient;
}

Vector3D Reflective::apply(const Vector3D inputNormal, const Vector3D location, const Vector3D cameraLocation, Light lightVector) {
	Vector3D finalColor;
	if(scenePtr->getReflectiveEnergy() > -1) { //If the ray hasn't hit too many reflective surfaces
		std::vector<Shape*> shapeVector = scenePtr->getShapeVector();
		float tMax = 1e7;
		Ray rayIn;
		HitStructure inputHit;
		rayIn.origin = location;
		Vector3D viewDirection = cameraLocation - location;
		Vector3D reflection = viewDirection - (2 * (viewDirection.dot(inputNormal)) * inputNormal);
		rayIn.direction = reflection;
		for(int i = 0; i < shapeVector.size(); i++)
			{
				shapeVector[i]->intersect(rayIn, 0.001, tMax, inputHit);
			}
			//Set pixel color
			if(inputHit.normal.length() != 0) { //Object was hit

				finalColor = inputHit.shader->getDiffuse() * inputHit.shader->getAmbient(); //Ambient color
/*
				//Shadow Generation
				Ray shadowRay;
				shadowRay.origin = inputHit.point;
				float tShadowMax;
				HitStructure shadowHit;
				bool hasDirectLight = false; //If false, need to calculate ambient color
				for(int j = 0; j < lightVector.size(); j++) {
					shadowRay.direction = lightVector[j].getPosition() - shadowRay.origin;
					tShadowMax = 1e7;
					for(int k = 0; k < shapeVector.size(); k++)
					{
						shapeVector[k]->intersect(shadowRay, 0.001, tShadowMax, shadowHit);
					}
					if(shadowHit.normal.length() == 0) { //No objects between primary object and light
						hasDirectLight = true;
						finalColor += inputHit.shader->apply(inputHit.normal, inputHit.point, mainCamera.getPosition(), lightVector[j]);
					}
				}
*/
			}
			if(type == "Glaze")
				finalColor = finalColor * reflectColor;
			finalColor.clamp(0,1);
	}
	else { //If the ray hits too many reflective surfaces
		finalColor.set(0,0,0);
	}
	return finalColor;
}
