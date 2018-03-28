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

#ifndef __APP_SYSTEM_LOGIC_H__
#define __APP_SYSTEM_LOGIC_H__

#define WIN32_LEAN_AND_MEAN
#include <UnigineLogic.h>
#include "NoesisGUI.h"

class AppSystemLogic : public Unigine::SystemLogic {
	
public:
	virtual int init();
	
	virtual int update();
	virtual int render();
	
	virtual int shutdown();

	NoesisGUI* noesisGUI;
};

#endif // __APP_SYSTEM_LOGIC_H__
