#define _ARMA_

class CfgPatches
{
	class FOGTriggers
	{
		units[] = {"FOGSign_Marker"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Sounds_Effects","DZ_Scripts","DZ_Characters","JM_CF_Scripts"};
	};
};
class CfgMods
{
	class FOGTriggers
	{
		dir = "FOGEventTriggers";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 0;
		name = "FOGEventTriggers";
		credits = "Hunterz";
		authorID = "0";
		version = "1.0";
		extra = 0;
		type = "mod";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"FOGEventTriggers/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"FOGEventTriggers/Scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"FOGEventTriggers/Scripts/5_Mission"};
			};
		};
	};
};
class CfgVehicles
{


	class House;
	class HouseNoDestruct;

	class FOGSign_Marker : HouseNoDestruct
	{
		scope = 2;
		model = "\FOGEventTriggers\models\sign_marker.p3d";
	};

};

class CfgSoundShaders
{
	class baseCharacter_SoundShader;

	class FOG_SoundShader1: baseCharacter_SoundShader
	{
		samples[] = {{"\FOGEventTriggers\sounds\teleport",1}};
		volume = 1;
		range = 60;
		rangeCurve[] = {{0,1},{0.5,0.7},{1,0}};
	};
	class FOG_SoundShader5: baseCharacter_SoundShader
	{
		samples[] = {{"\FOGEventTriggers\sounds\teleport",1}};
		volume = 1;
		range = 60;
		rangeCurve[] = {{0,1},{0.5,0.7},{1,0}};
	};
	class FOG_SoundShader2: baseCharacter_SoundShader
	{
		samples[] = {{"\FOGEventTriggers\sounds\attack_1",1}};
		volume = 1;
		range = 60;
		rangeCurve[] = {{0,1},{0.5,0.7},{1,0}};
	};
	class FOG_SoundShader3: baseCharacter_SoundShader
	{
		samples[] = {{"\FOGEventTriggers\sounds\gregorian_chant",1}};
		volume = 1;
		range = 60;
		rangeCurve[] = {{0,1},{0.5,0.7},{1,0}};
	};
	class FOG_SoundShader4: baseCharacter_SoundShader
	{
		samples[] = {{"\FOGEventTriggers\sounds\whisper",1}};
		volume = 1;
		range = 60;
		rangeCurve[] = {{0,1},{0.5,0.7},{1,0}};
	};

};


class CfgSoundSets
{
	//class baseCharacter_SoundSet;
	class FOG_SoundSet_300001			//teleport
	{
		soundShaders[] = {"FOG_SoundShader1"};
	};
	class FOG_SoundSet_200001			//teleport at target try
	{
		soundShaders[] = {"FOG_SoundShader5"};
	};
	class FOG_SoundSet_100001			//Zombie snort short
	{
		soundShaders[] = {"FOG_SoundShader2"};
	};
	class FOG_SoundSet_100002			//gregorian chant
	{
		soundShaders[] = {"FOG_SoundShader3"};
	};
	class FOG_SoundSet_630002			//30 secs of whisper
	{
		soundShaders[] = {"FOG_SoundShader4"};
	};

};

