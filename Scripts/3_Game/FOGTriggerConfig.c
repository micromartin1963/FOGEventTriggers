class FOGInfo
{
    string name;


    void FOGInfo(string nam) 
	{
        name = nam;
	}
}


class FOG__Info
{
	ref array< ref FOGInfo > FOGLocs;	
	void FOG__Info()
	{
	FOGLocs = new ref array< ref FOGInfo >;
	}
}


class FOGTriggerConfig
{

    protected const static string m_CfgRoot = "$profile:\\FOGTriggers\\";

    static void LoadConfig(string cfgName, out FOG__Info configData)
    {
        string configPath = m_CfgRoot + cfgName;

        if (!FileExist(configPath))
        {
	// --------------------------------------------------put an error message up and log todo
        }

        JsonFileLoader<FOG__Info>.JsonLoadFile(configPath, configData);
    }


}
