modded class DayZGame
{	
	protected ref FOG__Info m_FOGTriggerConfig;

	void DayZGame()
	{

	  
	}
	
    void SetFTRConfig(FOG__Info config)
    {
        m_FOGTriggerConfig = config;
    }

    FOG__Info GetFTRConfig()
    {
		return m_FOGTriggerConfig;
    }
};