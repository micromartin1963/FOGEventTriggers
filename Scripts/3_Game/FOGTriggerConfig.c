


class FOGInfo
{
    string LocationName;
    int TType;
    string FogText;
    string OrigVectorStr;
    string TargetVectorStr;
    string FogRadius;
    string FogClassnameStr;
    int FogSoundIndex;
 


    void FOGInfo(string loc,int Type,string nam,string v,string v2,string rad,string cn,int index) 
	{
	LocationName = loc;
	TType = Type;
        FogText = nam;
	OrigVectorStr = v;
	TargetVectorStr = v2;
	FogRadius = rad;
	FogClassnameStr = cn;
	FogSoundIndex = index;
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

	static void LoadConfig(string cfgName, out FOG__Info cfgDataSet)
	{
        string configPath = m_CfgRoot + cfgName;

    	    if (!FileExist(configPath))    //------------------------------------ we need a logger to do this properly
        	{
		// --------------------------------------------------put an error message up and log todo
		Print("XXXXXXXXXXXXXX not found Config ERROR default created in --> "+ configPath);
		MyConfig(cfgDataSet);
		SaveCfg(cfgName,cfgDataSet);
		return;
	        }
		else
		{
		Print("FOG Config Found OK");
		}
        JsonFileLoader<FOG__Info>.JsonLoadFile(configPath, cfgDataSet);
	}


	protected static void MyConfig(out FOG__Info cfgDataSet)
	{
        cfgDataSet = new FOG__Info();
	cfgDataSet.FOGLocs.Insert( new FOGInfo("Beach location 1", 2, "FOG_SoundSet_002", "10810 4 2266", "10825 4 2278", "6.2", "ZmbF_BlueCollarFat_Blue", 2,  ));  // need better default
	}



    protected static void SaveCfg(string cfgName, FOG__Info cfgDataSet)
    {
        string Path =  m_CfgRoot + cfgName;

	if (!FileExist(m_CfgRoot))
	{
	MakeDirectory(m_CfgRoot);
        }

        JsonFileLoader<FOG__Info>.JsonSaveFile(Path, cfgDataSet);
    }









}
