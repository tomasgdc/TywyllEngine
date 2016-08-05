#ifndef _GAME_OPTIONS_H_
#define _GAME_OPTIONS_H_


struct GameOptions
{
	//Level options
	std::string m_strLevel;

	// Rendering options
	std::string m_Renderer;
	bool m_runFullSpeed;

	// Sound options
	float m_soundEffectsVolume;
	float m_musicVolume;


	void Init(const char* xmlFilePath, LPWSTR lpCmdLine);
};
#endif
