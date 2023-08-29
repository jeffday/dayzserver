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
		ItemBase bullets;
		EntityAI head, face, eyes, torso, belt, knife, legs, feet, hands, meleeContainer, melee, beltSheath, holster, rifle, shotgun, sniper, bag, pistolAmmoPouch, beltAmmoPouch, chestAmmoPouch, pistol, chest, bandages, rangefinder, itemEnt;

		head = player.GetInventory().CreateInInventory("BeanieHat_Blue");

		face = player.GetInventory().CreateInInventory("MMG_facemask_black");
		eyes = player.GetInventory().CreateInInventory("FP4_Black_Glasses");
		torso = player.GetInventory().CreateInInventory("MMG_combatshirt_police");
		legs = player.GetInventory().CreateInInventory("MMG_combatpants_police");
		hands = player.GetInventory().CreateInInventory("FP4_MiniGloves_black");
		feet = player.GetInventory().CreateInInventory("SK8_Sneakers_FullBlack");

		// belt

		belt = player.GetInventory().CreateInInventory("MMG_falcon_b1_belt_black");
		belt.GetInventory().CreateAttachment("MMG_carbine_black");

		holster = belt.GetInventory().CreateAttachment("MMG_Holster_black");
		beltSheath = belt.GetInventory().CreateAttachment("Spur_KnifeSheath_Black");
		// pistolAmmoPouch = belt.GetInventory().CreateAttachment("mmg_dump_pouch_black");
		beltAmmoPouch = belt.GetInventory().CreateAttachment("MMG_tactical_pouch_black");

		// chest slot

		chest = player.GetInventory().CreateInInventory("MMG_chestrig_black");
		chestAmmoPouch = chest.GetInventory().CreateAttachment("MMG_ammo_pouch_black");
		chest.GetInventory().CreateAttachment("Spur_KnifeSheath_Black");

		// bag

		bag = player.GetInventory().CreateInInventory("MMG_assault_pack_black");
		bag.GetInventory().CreateAttachment("Chemlight_White");
		bag.GetInventory().CreateInInventory("LeatherSewingKit");
		bag.GetInventory().CreateInInventory("WeaponCleaningKit");
		bandages = bag.GetInventory().CreateInInventory("BandageDressing");

		// rangefinder = bag.GetInventory().CreateInInventory("Rangefinder");
		// rangefinder.GetInventory().CreateAttachment("Battery9V");

		// weapons

		knife = beltSheath.GetInventory().CreateAttachment("Scara_Skeleton");
		beltSheath.GetInventory().CreateAttachment("Whetstone");

		// meleeContainer = player.GetInventory().CreateInInventory("FP4_Nodaty_Sheath");
		// melee = meleeContainer.GetInventory().CreateAttachment("FP4_Nodaty");

		// shotgun = player.GetInventory().CreateInInventory("BO_SPAS12_SemiAuto");
		// shotgun.GetInventory().CreateAttachment("BO_SPAS12_Suppressor");

		rifle = bag.GetInventory().CreateAttachment("BO_M4A1_CQB");
		rifle.GetInventory().CreateAttachment("BO_LeupoldCarbineOptics");
		rifle.GetInventory().CreateAttachment("BO_LegionSuppressor_Black");

		// sniper = player.GetInventory().CreateInInventory("BO_SV98");
		// sniper.GetInventory().CreateAttachment("BO_Sight_4_6");

		pistol = holster.GetInventory().CreateAttachment("HH_Beretta92");
		pistol.GetInventory().CreateAttachment("Tundra_Suppressor");

		// sidearm ammo

		// for(int i = 0; i < 4; i++) {
        //      pistolAmmoPouch.GetInventory().CreateInInventory("HH_Beretta92_Mag");
        // }
		// for(i = 0; i < 3; i++) {
        //      pistolAmmoPouch.GetInventory().CreateInInventory("AmmoBox_9x19_25rnd");
        // }
		// bullets = pistolAmmoPouch.GetInventory().CreateInInventory("Ammo_9x19");
		// bullets.SetQuantity(25);

		// primary ammo

		for(int i = 0; i < 4; i++) {
             chestAmmoPouch.GetInventory().CreateInInventory("BO_Mag_PMAGWindow_30rnd");
        }
		// for(i = 0; i < 11; i++) {
        //      chestAmmoPouch.GetInventory().CreateInInventory("AmmoBox_556x45_20Rnd");
        // }
		bullets = chestAmmoPouch.GetInventory().CreateInInventory("Ammo_556x45");
		bullets.SetQuantity(1);

		// secondary ammo

		for(i = 0; i < 4; i++) {
			beltAmmoPouch.GetInventory().CreateInInventory("HH_Beretta92_Mag");
        }

		// for(i = 0; i < 3; i++) {
		// 	beltAmmoPouch.GetInventory().CreateInInventory("AmmoBox_9x19_25rnd");
        // }

		bullets = beltAmmoPouch.GetInventory().CreateInInventory("Ammo_9x19");
		bullets.SetQuantity(1);

		// hotkeys

		// player.SetQuickBarEntityShortcut( melee, 0 );
		player.SetQuickBarEntityShortcut( knife, 1 );
		player.SetQuickBarEntityShortcut( pistol, 2 );
		player.SetQuickBarEntityShortcut( rifle, 3 );
		player.SetQuickBarEntityShortcut( bandages, 4 );
		// player.SetQuickBarEntityShortcut( rangefinder, 5 );
		// player.SetQuickBarEntityShortcut( sniper, 6 );
		// player.SetQuickBarEntityShortcut( shotgun, 7 );
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
