/*
  NoesisGUI - Unigine Integration
  Copyright (c) 2014-2018 R&D Lab. All right reserved.
  office@researchdevelopinglab.com
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*/ 

#include "AppSystemLogic.h"

using namespace Unigine;

int AppSystemLogic::init() {
	// Write here code to be called on engine initialization.
	noesisGUI = &NoesisGUI::getInstance();
	//NoesisGUI* noesisGUI = new NoesisGUI();
	noesisGUI->Initialize();
	noesisGUI->LoadUI("start.xaml");
	
	return 1;
}

// start of the main loop
int AppSystemLogic::update() {
	// Write here code to be called before updating each render frame.
	noesisGUI->Update();
	
	return 1;
}

int AppSystemLogic::render() {
	// Write here code to be called before rendering each render frame.
	noesisGUI->Render();
	
	return 1;
}
// end of the main loop

int AppSystemLogic::shutdown() {
	// Write here code to be called on engine shutdown.
	noesisGUI->Shutdown();
	
	return 1;
}