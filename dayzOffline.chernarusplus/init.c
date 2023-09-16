void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 4, reset_day = 30;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, 5, 30);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, 5, 30);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, 5, 30);
			}
		}
	}
}

class CustomMission: MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		// this piece of code is recommended otherwise event system is switched on automatically and runs from default values
		// comment this whole block if NOT using Namalsk Survival
		if ( m_EventManagerServer )
		{
			// enable/disable event system, min time between events, max time between events, max number of events at the same time
			m_EventManagerServer.OnInitServer( true, 550, 1000, 2 );
			// registering events and their probability
			m_EventManagerServer.RegisterEvent( Aurora, 0.01 );
			m_EventManagerServer.RegisterEvent( Blizzard, 0.0 );
			m_EventManagerServer.RegisterEvent( ExtremeCold, 0.0 );
			m_EventManagerServer.RegisterEvent( Snowfall, 0.0 );
			m_EventManagerServer.RegisterEvent( EVRStorm, 0.99 );
			m_EventManagerServer.RegisterEvent( HeavyFog, 0.0 );
		}
	}

	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			float rndHlt = Math.RandomFloat( 0.45, 0.65 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}
    
    EntityAI SpawnWithRandomHealth(PlayerBase player, string itemName)
    {
    	EntityAI itemEnt;
    
    	itemEnt = player.GetInventory().CreateInInventory(itemName);
        SetRandomHealth( itemEnt );
        
        return itemEnt;
    }

    void spawnItemNTimesOnPlayer(PlayerBase player, string item, int n) {
        for(int i = 0; i < n; i++) {
            player.GetInventory().CreateInInventory(item);
        }
    }

    void spawnItemsOnPlayer(PlayerBase player, TStringArray items) {
        for(int i = 0; i < items.Count(); i++) {
             player.GetInventory().CreateInInventory(items[i]);
        }
    }

    void spawnItemWithAttachments(PlayerBase player, string parentItem, TStringArray attachments) {
        EntityAI itemEnt;
        
        itemEnt = player.GetInventory().CreateInInventory(parentItem);

        for(int i = 0; i < attachments.Count(); i++) {
            itemEnt.GetInventory().CreateAttachment(attachments[i]);
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

    void SpawnJeffSetup(PlayerBase player) {
		EntityAI bandages;

		player.GetInventory().CreateInInventory("BeanieHat_Red");

		player.GetInventory().CreateInInventory("ThickFramesGlasses");
		player.GetInventory().CreateInInventory("ParamedicJacket_Crimson");
		player.GetInventory().CreateInInventory("ParamedicPants_Crimson");
		player.GetInventory().CreateInInventory("YRTSK_VansSneakers_Red");
		player.GetInventory().CreateInInventory("SurgicalGloves_Blue");
		player.GetInventory().CreateInInventory("CanvasBag_Medical");

		bandages = player.GetInventory().CreateInInventory("BandageDressing");
		player.GetInventory().CreateInInventory("Chemlight_White");

		// hotkeys

		player.SetQuickBarEntityShortcut( bandages, 4 );
    }

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		EntityAI itemClothing;

		itemClothing = player.FindAttachmentBySlotName( "Body" );
		if ( itemClothing )
		{
			player.RemoveAllItems();
            
            SpawnJeffSetup(player);
		} 
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}
