#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());

	for (int base_x = -60; base_x <= 60; base_x += 15) {

		for (int base_z = -60; base_z <= 60; base_z += 15) {

			auto noise_value = ofMap(ofNoise(base_x * 0.003, base_z * 0.003, ofGetFrameNum() * 0.0015), 0, 1, 0, 10);
			int int_noise_value = noise_value;

			for (int i = 0; i < 10; i++) {

				if (i < int_noise_value) {

					ofPushMatrix();
					ofTranslate(base_x, -150 + i * 15, base_z);

					ofSetColor(39);
					ofFill();
					ofDrawBox(15);

					ofSetColor(239);
					ofNoFill();
					ofDrawBox(15);

					ofPopMatrix();
				}
				else if (int_noise_value < i) {

					ofPushMatrix();
					ofTranslate(base_x, 150 - (10 - i) * 15, base_z);

					ofSetColor(39);
					ofFill();
					ofDrawBox(15);

					ofSetColor(239);
					ofNoFill();
					ofDrawBox(15);

					ofPopMatrix();
				}
				else {

					auto top = glm::vec3(0, -150 + i * 15, 0);
					auto bottom = glm::vec3(0, 150 - (10 - i) * 15, 0);

					auto param = noise_value - int_noise_value;

					auto location = bottom + (top - bottom) * param;
					location += glm::vec3(base_x, 0, base_z);

					ofColor fill_color(239);
					ofColor no_fill_color(39);

					if (param < 0.2) {

						fill_color = ofColor(ofMap(param, 0, 0.2, 39, 239));
						no_fill_color = ofColor(ofMap(param, 0, 0.2, 239, 39));
					}
					else if(0.8 < param) {

						fill_color = ofColor(ofMap(param, 1, 0.8, 39, 239));
						no_fill_color = ofColor(ofMap(param, 1, 0.8, 239, 39));
					}

					ofPushMatrix();
					ofTranslate(location);

					ofSetColor(fill_color);
					ofFill();
					ofDrawBox(15);

					ofSetColor(no_fill_color);
					ofNoFill();
					ofDrawBox(15);

					ofPopMatrix();
				}
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}