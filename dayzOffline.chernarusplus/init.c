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
			m_EventManagerServer.RegisterEvent( Aurora, 0.1 );
			m_EventManagerServer.RegisterEvent( Blizzard, 0.0 );
			m_EventManagerServer.RegisterEvent( ExtremeCold, 0.0 );
			m_EventManagerServer.RegisterEvent( Snowfall, 0.0 );
			m_EventManagerServer.RegisterEvent( EVRStorm, 0.9 );
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
        autoptr TStringArray clothes = {"BaseballCap_Black","MMG_facemask_black","FP4_Black_Glasses","MMG_combatshirt_black","MMG_combatpants_black","SK8_Sneakers_FullBlack","WoolGloves_Black"};

        spawnItemsOnPlayer(player, clothes);

		ItemBase bullets;
		EntityAI sheath, rifle, bag, belt, itemEnt, holster, pistol;

		sheath = player.GetInventory().CreateInInventory("FP4_Nodaty_Sheath");
		itemEnt = sheath.GetInventory().CreateAttachment("FP4_Nodaty");

		player.SetQuickBarEntityShortcut( itemEnt, 0 );

		rifle = player.GetInventory().CreateInInventory("Mosin9130_Black");
		rifle.GetInventory().CreateAttachment("PUScopeOptic");

		player.SetQuickBarEntityShortcut( rifle, 6 );

        belt = player.GetInventory().CreateInInventory("MMG_falcon_b1_belt_black");
		holster = belt.GetInventory().CreateAttachment("MMG_Holster_black");
		pistol = holster.GetInventory().CreateAttachment("HH_Beretta92");

		player.SetQuickBarEntityShortcut( pistol, 2 );

		itemEnt = belt.GetInventory().CreateAttachment("Spur_KnifeSheath_Black");
		itemEnt = itemEnt.GetInventory().CreateAttachment("Scara_Nomad");
		player.SetQuickBarEntityShortcut( itemEnt, 1 );

		belt.GetInventory().CreateAttachment("MMG_carbine_black");
		itemEnt = belt.GetInventory().CreateAttachment("mmg_dump_pouch_black");
		for(int i = 0; i < 3; i++) {
             itemEnt.GetInventory().CreateInInventory("HH_Beretta92_Mag");
        }
		bullets = itemEnt.GetInventory().CreateInInventory("Ammo_9x19");
		bullets.SetQuantity(25);

		itemEnt = belt.GetInventory().CreateAttachment("MMG_tactical_pouch_black");
		for(i = 0; i < 11; i++) {
             itemEnt.GetInventory().CreateInInventory("AmmoBox_762x54_20Rnd");
        }

		bullets = itemEnt.GetInventory().CreateInInventory("AmmoBox_762x54_20Rnd");
		bullets.SetQuantity(20);

		// harness

		itemEnt = player.GetInventory().CreateInInventory("MMG_chestrig_black");
		itemEnt.GetInventory().CreateAttachment("Spur_KnifeSheath_Black");

		itemEnt = itemEnt.GetInventory().CreateAttachment("MMG_ammo_pouch_black");
		
		bag = player.GetInventory().CreateInInventory("FP4_HuntingTOP_Bag_BLACK");

		bag.GetInventory().CreateAttachment("Chemlight_White");
		itemEnt = bag.GetInventory().CreateInInventory("BandageDressing");
		player.SetQuickBarEntityShortcut(itemEnt, 4);
    }

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;

		itemClothing = player.FindAttachmentBySlotName( "Body" );
		if ( itemClothing )
		{
			player.RemoveAllItems();
            
            SpawnJeffSetup(player);
			
            itemEnt = player.GetInventory().CreateInInventory("WaterBottle");
			itemBs = player.GetInventory().CreateInInventory("PurificationTablets");
			itemBs.SetQuantity(1);

            itemEnt = player.GetInventory().CreateInInventory("PowderedMilk");
			itemEnt = player.GetInventory().CreateInInventory("ChernarusMap");
			itemEnt = player.GetInventory().CreateInInventory("CanOpener");
		} 
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}
