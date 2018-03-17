/*
 * ERMScriptModule.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"
#include "ERMScriptModule.h"

#include "ERMInterpreter.h"

#ifdef __GNUC__
#define strcpy_s(a, b, c) strncpy(a, c, b)
#endif

const char *g_cszAiName = "(V)ERM interpreter";

extern "C" DLL_EXPORT void GetAiName(char* name)
{
	strcpy_s(name, strlen(g_cszAiName) + 1, g_cszAiName);
}

extern "C" DLL_EXPORT void GetNewModule(std::shared_ptr<scripting::Module> &out)
{
	out = std::make_shared<ERMScriptModule>();
}

ERMScriptModule::ERMScriptModule()
{

}

std::string ERMScriptModule::compile(const std::string & name, const std::string & source) const
{
	std::shared_ptr<ERMInterpreter> interp = std::make_shared<ERMInterpreter>(logMod);

	interp->loadScript(name, source);
	interp->scanScripts();

	return interp->convert();
}

std::shared_ptr<scripting::ContextBase> ERMScriptModule::createContextFor(const scripting::Script * source, const scripting::Environment * env) const
{
	throw std::runtime_error("ERM context creation is not possible");
}

void ERMScriptModule::registerSpellEffect(spells::effects::Registry * registry, const scripting::Script * source) const
{
	throw std::runtime_error("ERM spell effect registration is not possible");
}
