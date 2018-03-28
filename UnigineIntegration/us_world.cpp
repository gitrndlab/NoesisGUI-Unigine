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

#include <core/unigine.h>
// This file is in UnigineScript language.
// World script, it takes effect only when the world is loaded.


int init() {

	NoesisGUIObject noesis_gui = new NoesisGUIObject();
	noesis_gui = extern_object.getInstance();
	noesis_gui.LoadUIbyUS("start.xaml");

	return 1;
}