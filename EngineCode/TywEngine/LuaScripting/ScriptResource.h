#ifndef _ENGINE_SCRIPT_RESOURCE_H_
#define _ENGINE_SCRIPT_RESOURCE_H_

class TYWENGINE_API ScriptResourceLoader
{
	virtual bool VLoadResource(char* rawBuffer, uint32_t rawSize);
	virtual std::string VGetPattern() { return "*.lua"; }
};

#endif