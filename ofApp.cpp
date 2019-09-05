#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int radius = 90;
	int deg_span = 10;
	int span = 220;
	bool rotate = false;
	for (int x = -span; x <= span; x += span) {

		for (int y = -span; y <= span; y += span) {

			ofPushMatrix();
			ofTranslate(x, y);
			if (rotate) { ofRotateX(90); }
			rotate = !rotate;

			auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
			for (int deg = 0; deg < 360; deg += deg_span) {

				auto outer_location = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0);
				ofDrawSphere(outer_location, 2);

				auto inner_location = glm::vec3(radius * 0.5 * cos(deg * DEG_TO_RAD), radius * 0.5 * sin(deg * DEG_TO_RAD), 0);
				auto angle_x = ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * 0.003), 0, 1, -PI, PI);
				auto angle_y = ofMap(ofNoise(noise_seed.y, ofGetFrameNum() * 0.003), 0, 1, -PI, PI);
				auto angle_z = ofMap(ofNoise(noise_seed.z, ofGetFrameNum() * 0.003), 0, 1, -PI, PI);
				auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
				auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
				auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));
				inner_location = glm::vec4(inner_location, 0) * rotation_z * rotation_y * rotation_x;

				ofDrawSphere(inner_location, 2);
				ofDrawLine(outer_location, inner_location);
			}

			ofPopMatrix();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}