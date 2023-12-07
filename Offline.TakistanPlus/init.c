void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	/*
	  [Takistan] Weather init
	   Warning: DO NOT ALTER following values as they are interconnected with Takistan weather system!
	   To ensure correct functionality, it is necessary to include weaher init AFTER the hive init.
	*/
	Weather weather = GetGame().GetWeather();
	weather.MissionWeather( true );
	weather.GetOvercast().SetLimits( 0.0, 0.30 );
	weather.GetRain().SetLimits( 0.0, 0.0 );
	weather.GetFog().SetLimits( 0.0, 0.0 );
	weather.GetOvercast().SetForecastChangeLimits( 0.1, 0.3 );
	weather.GetOvercast().SetForecastTimeLimits( 1600, 2100 );
	weather.GetOvercast().Set( 0.0, 0, 0 );
	weather.GetRain().Set( 0, 0, 0 );
	weather.GetFog().Set( 0, 0, 0 );
	weather.SetWindMaximumSpeed( 30 );
	weather.SetWindFunctionParams( 0.1, 1.0, 42 );
	weather.SetStorm( 1, 0.7, 30 );
	weather.SetRainThresholds( 0.0, 1.0, 0 );

	/*
	  [Takistan] Mission time init
	   after CE init to determine if storage mission type is outside of the required time-frame
	*/
	int year, month, day, hour, minute;
	GetGame().GetWorld().GetDate( year, month, day, hour, minute );
    if ( ( month > 9 ) || ( month <= 6 ) )
    {
    	year = 2011;
        month = 7;
        day = 1;
		
		// hardcode to 5 AM start so it's not balls hot when you first spawn
		GetGame().GetWorld().SetDate( year, month, day, 5, minute );
	}
}

class CustomMission: MissionServer
{
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			float rndHlt = Math.RandomFloat( 0.25, 0.65 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}

	override void OnInit()
	{
		super.OnInit();

		// this piece of code is recommended otherwise the event system is switched on automatically and runs from default values
		if ( m_EventManager )
		{
			// min time between events, max time between events, max number of events at the same time
			m_EventManager.Run( 900, 1800, 1 );
			// registering events and their probability
			m_EventManager.RegisterEvent( Sandstorm, 1.0 );
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );
		Class.CastTo( m_player, playerEnt );

		GetGame().SelectPlayer( identity, m_player );

		return m_player;
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;

		itemClothing = player.FindAttachmentBySlotName( "Body" );
		{
			itemEnt = player.GetInventory().CreateInInventory("Compass");

            itemEnt = player.GetInventory().CreateInInventory("SodaCan_Pipsi");

            itemEnt = player.GetInventory().CreateInInventory("BandageDressing");

            itemEnt = player.GetInventory().CreateInInventory("TunaCan");
			
			itemEnt = player.GetInventory().CreateInInventory("Chemlight_White");			
			
		};
		if ( itemClothing )
		{
			SetRandomHealth( itemClothing );
			
			itemEnt = itemClothing.GetInventory().CreateInInventory( "TunaCan" );
						if ( Class.CastTo( itemBs, itemEnt ) )
				itemBs.SetQuantity( 4 );

			SetRandomHealth( itemEnt );

			string chemlightArray[] = { "Chemlight_White", "Chemlight_Yellow", "Chemlight_Green", "Chemlight_Red" };
			int rndIndex = Math.RandomInt( 0, 4 );
			itemEnt = itemClothing.GetInventory().CreateInInventory( chemlightArray[rndIndex] );
			SetRandomHealth( itemEnt );
		}
		
		itemClothing = player.FindAttachmentBySlotName( "Legs" );
		if ( itemClothing )
			SetRandomHealth( itemClothing );
		
		itemClothing = player.FindAttachmentBySlotName( "Feet" );
		if ( itemClothing )
			SetRandomHealth( itemClothing );
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}