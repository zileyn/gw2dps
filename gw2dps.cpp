#include "gw2lib.h"
#include "gw2dps/gw2dps.h"

// Settings //
bool killApp = false;

bool help = false;
bool expMode = false;
bool selfFloat = false;
bool selfHealthPercent = true;
bool loopLimiter = true;

bool targetSelected = true;
bool targetInfo = false;
bool targetInfoAlt = false;
bool targetLock = false;

bool dpsAllowNegative = false;

bool logDps = true;
bool logDpsDetails = false;
string logDpsFile = "gw2dpsLog-Dps.txt";

bool logKillTimer = false;
bool logKillTimerDetails = false;
bool logKillTimerToFile = false;

bool logHits = false;
bool logHitsDetails = false;
bool logHitsToFile = false;
string logHitsFile = "gw2dpsLog-Hits.txt";
int threadHitsCounter = 0;

bool logAttackRate = false;
bool logAttackRateDetails = false;
bool logAttackRateToFile = false;
int AttackRateChainHits = 1;
int AttackRateChainTime = 0; // not used atm
string logAttackRateFile = "gw2dpsLog-AttackRate.txt";
int threadAttackRateCounter = 0;

bool alliesList = false;
int wvwBonus = 0;

bool floatAllyNpc = false;
bool floatEnemyNpc = false;
bool floatAllyPlayer = false;
bool floatAllyPlayerProf = false;
bool floatEnemyPlayer = false;
bool floatSiege = false;
int floatRadius = 7000;
bool floatCircles = false;
bool floatType = true; // false = HP; true = Dist;

bool logSpeedometer = false;
bool logSpeedometerEnemy = false;
int logDisplacementValue = 0;
bool logDisplacement = false;
bool logDisplacementEnemy = false;
Vector3 logDisplacementStart = Vector3(0, 0, 0);

// Threads //
#include "gw2dps/thread.Hotkeys.cpp"
#include "gw2dps/thread.Dps.cpp"
#include "gw2dps/thread.KillTimer.cpp"
#include "gw2dps/thread.Hits.cpp"
#include "gw2dps/thread.AttackRate.cpp"
#include "gw2dps/thread.Speedometer.cpp"

// Self
Character me;
Agent meAg = me.GetAgent();

void ESP()
{
	// Element Anchors
	Anchor aLeft, aTopLeft, aTop, aTopRight, aRight, aCenter, aBottom;

	aLeft.x = 100;
	aLeft.y = 75;

	aTopLeft.x = round((GetWindowWidth() / 2 - 316 - 179) / 2 + 316);
	aTopLeft.y = 8;

	aTop.x = round(GetWindowWidth() / 2);
	aTop.y = 1;

	aTopRight.x = round((GetWindowWidth() / 2 - 294 - 179) / 2 + GetWindowWidth() / 2 + 179);
	aTopRight.y = 8;

	aRight.x = GetWindowWidth() - 10;
	aRight.y = 8;

	aCenter.x = round(GetWindowWidth() * float(0.5));
	aCenter.y = round(GetWindowHeight() * float(0.5));

	aBottom.x = round(GetWindowWidth() * float(0.5));
	aBottom.y = round(GetWindowHeight() - float(85));


	if (help){
		stringstream ss;
		//ss << format("[%i] Exp Mode Crosshair (Alt H)\n") % expMode;
		//ss << format("\n");
		ss << format("[%i] Self Health Percent (Alt P)\n") % selfHealthPercent;
		ss << format("\n");
		ss << format("[%i] Selected/Locked Target HP (Alt S)\n") % targetSelected;
		ss << format("[%i] Selected Target Details (Alt I)\n") % targetInfo;
		ss << format("[%i] Lock On Target (Alt L)\n") % targetLock;
		ss << format("[%i] Allow Negative DPS (Alt N)\n") % dpsAllowNegative;
		ss << format("\n");
		ss << format("[%i] DPS Meter (Alt D)\n") % logDps;
		ss << format("[%i] DPS Meter History (Alt Shift D)\n") % logDpsDetails;
		ss << format("\n");
		ss << format("[%i] Kill Timer (Alt Num7)\n") % logKillTimer;
		ss << format("[%i] Kill Timer Details (Alt Num1)\n") % logKillTimerDetails;
		//ss << format("[%i] Kill Timer Writes to a File (Alt Num4)\n") % logKillTimerToFile;
		ss << format("\n");
		ss << format("[%i] Monitor Hits (Alt Num8)\n") % logHits;
		ss << format("[%i] Show Hits History (Alt Num2)\n") % logHitsDetails;
		ss << format("[%i] Record Hits to File (Alt Num5)\n") % logHitsToFile;
		ss << format("\n");
		ss << format("[%i] Monitor Attack Rate (Alt Num9)\n") % logAttackRate;
		ss << format("[%i] Show Attack Rate History (Alt Num3)\n") % logAttackRateDetails;
		ss << format("[%i] Record Attack Rate to File (Alt Num6)\n") % logAttackRateToFile;
		ss << format("[%i] Adjust Attack Rate Threshold (Alt PgUp/PgDown)\n") % AttackRateChainHits;
		ss << format("\n");
		ss << format("[%i] Nearby Ally Players List (Alt C)\n") % alliesList;
		ss << format("[%i] Adjust WvW HP Bonus (Alt Home/End)\n") % wvwBonus;
		ss << format("\n");
		ss << format("[%i] Count Ally NPCs (Alt 1)\n") % floatAllyNpc;
		ss << format("[%i] Count Enemy NPCs (Alt 2)\n") % floatEnemyNpc;
		ss << format("[%i] Count Ally Players (Alt 3)\n") % floatAllyPlayer;
		ss << format("[%i] Count Enemy Players (Alt 4)\n") % floatEnemyPlayer;
		//ss << format("[%i] Count Siege (Alt 5)\n") % floatSiege;
		ss << format("[%i] Show/Hide Floaters below counted (Alt F)\n") % floatCircles;
		ss << format("[%i] Floaters show Max HP / Distance (Alt Shift F)\n") % floatType;
		ss << format("\n");
		ss << format("[%i] Speedometer (Alt 9)\n") % logSpeedometer;
		ss << format("[%i] Speedometer for Self/Enemy (Alt Shift 9)\n") % logSpeedometerEnemy;
		ss << format("[%i] Measure Distance (Alt 0)\n") % logDisplacement;
		ss << format("[%i] Distance for Self/Enemy (Alt Shift 0)\n") % logDisplacementEnemy;

		StrInfo strInfo;
		strInfo = StringInfo(ss.str());
		float x = round(aCenter.x - strInfo.x / 2);
		float y = round(aCenter.y - strInfo.y / 2);

		DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
		DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
		font.Draw(x, y, fontColor - (!loopLimiter ? 0x00aa0000 : 0), ss.str());
	}

	// JP Skills
	if (expMode)
	{
		float x = aCenter.x;
		float y = aCenter.y + 28;
		
		float box = 2;
		float line = 10;

		DrawLine(x - line, y, x + line, y, borderColor);
		DrawLine(x, y - line, x, y + line, borderColor);

		DrawRectFilled(x - box, y - box, box * 2, box * 2, 0xccFF0000);
		DrawRect(x - box, y - box, box * 2, box * 2, borderColor);
	}

	if (selfFloat)
	{
		DWORD color = 0x4433ff00;
		DrawCircleProjected(self.pos, 20.0f, color);
		DrawCircleFilledProjected(self.pos, 20.0f, color - 0x30000000);
	}

	// Font Draw Debug
	if (0) {
		stringstream ss;
		ss << format("Selected: 18,140 / 18,140 [100%s]") % "%%";
		ss << format("Locked: 18,140 / 18,140 [100%s]") % "%%";

		StrInfo strInfo;
		strInfo = StringInfo(ss.str());
		float x = 0;
		float y = float(strInfo.lineCount * lineHeight + 1);
		padX = 0;
		padY = 0;

		DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, 0xffffffff);
		font.Draw(x, y, 0xff000000, ss.str());

		return;
	}

	// Targets & Agents //
	me = GetOwnCharacter();
	if (me.IsValid()){
		self.id = GetOwnAgent().GetAgentId();
		self.pos = GetOwnAgent().GetPos();

		self.cHealth = int(me.GetCurrentHealth());
		self.mHealth = int(me.GetMaxHealth());
		if (self.mHealth > 0)
			self.pHealth = int(100.f * float(self.cHealth) / float(self.mHealth));
		else
			self.pHealth = 0;

		self.lvl = me.GetScaledLevel();
		self.lvlActual = me.GetLevel();
		self.alive = me.IsAlive();
	}
	Agent agLocked = GetLockedSelection();
	if (agLocked.IsValid())
	{
		if (agLocked.GetAgentId() != selected.id)
			selected = {};

		int agType = agLocked.GetType();
		if (agType == GW2::AGENT_CATEGORY_CHAR) // char
		{
			selected.valid = true;
			selected.id = agLocked.GetAgentId();
			selected.type = agType;

			selected.pos = agLocked.GetPos();

			Character chLocked = agLocked.GetCharacter();
			selected.cHealth = int(chLocked.GetCurrentHealth());
			selected.mHealth = int(chLocked.GetMaxHealth());
			if (selected.mHealth > 0)
				selected.pHealth = int(100.f * float(selected.cHealth) / float(selected.mHealth));
			else
				selected.pHealth = 0;
			selected.lvl = chLocked.GetScaledLevel();
			selected.lvlActual = chLocked.GetLevel();
		}
		else if (agType == GW2::AGENT_TYPE_GADGET) // structure
		{
			selected.valid = true;
			selected.id = agLocked.GetAgentId();
			selected.type = agType;

			selected.pos = agLocked.GetPos();

			unsigned long shift = *(unsigned long*)agLocked.m_ptr;
			shift = *(unsigned long*)(shift + 0x30);
			shift = *(unsigned long*)(shift + 0x168);
			if (shift)
			{
				selected.cHealth = int(*(float*)(shift + 0x8));
				selected.mHealth = int(*(float*)(shift + 0xC));
			}
			if (selected.mHealth > 0)
				selected.pHealth = int(100.f * float(selected.cHealth) / float(selected.mHealth));
			else
				selected.pHealth = 0;
			//selected.lvl = chLocked.GetScaledLevel();
			//selected.lvlActual = chLocked.GetLevel();
		}
		else if (agType == GW2::AGENT_TYPE_GADGET_ATTACK_TARGET) // world boss
		{
			selected.valid = true;
			selected.id = agLocked.GetAgentId();
			selected.type = agType;

			selected.pos = agLocked.GetPos();

			unsigned long shift = *(unsigned long*)agLocked.m_ptr;
			shift = *(unsigned long*)(shift + 0x30);
			shift = *(unsigned long*)(shift + 0x28);
			shift = *(unsigned long*)(shift + 0x17c);
			if (shift)
			{
				selected.cHealth = int(*(float*)(shift + 0x8));
				selected.mHealth = int(*(float*)(shift + 0xC));
			}
			if (selected.mHealth > 0)
				selected.pHealth = int(100.f * float(selected.cHealth) / float(selected.mHealth));
			else
				selected.pHealth = 0;

			//selected.lvl = chLocked.GetScaledLevel();
			//selected.lvlActual = chLocked.GetLevel();
		}
		else
			selected = {};

		if (selected.mHealth == 0)
			selected = {};
	}
	else
		selected = {};

	// Locked Target (ID)
	if (targetLock)
	{
		if (!locked.valid && selected.valid)
			targetLockID = selected.id;
	}
	else
	{
		if (!selected.valid)
		{
			locked = {};
			targetLockID = 0;
		}
		else
			targetLockID = selected.id;
	}

	// compile all agent data
	Floaters floaters;
	Allies allies;
	Agent ag;
	while (ag.BeNext())
	{
		// Locked Target (Data)
		if (targetLockID == ag.GetAgentId())
		{
			int agType = ag.GetType();
			if (agType == GW2::AGENT_CATEGORY_CHAR) // char
			{
				locked.valid = true;
				locked.id = ag.GetAgentId();
				locked.type = agType;

				locked.pos = ag.GetPos();

				Character ch = ag.GetCharacter();
				locked.cHealth = int(ch.GetCurrentHealth());
				locked.mHealth = int(ch.GetMaxHealth());
				if (locked.mHealth > 0)
					locked.pHealth = int(100.f * float(locked.cHealth) / float(locked.mHealth));
				else
					locked.pHealth = 0;
				locked.lvl = ch.GetScaledLevel();
				locked.lvlActual = ch.GetLevel();

				
			}
			else if (agType == GW2::AGENT_TYPE_GADGET) // structure
			{
				locked.valid = true;
				locked.id = ag.GetAgentId();
				locked.type = agType;

				locked.pos = ag.GetPos();

				unsigned long shift = *(unsigned long*)ag.m_ptr;
				shift = *(unsigned long*)(shift + 0x30);
				shift = *(unsigned long*)(shift + 0x168);
				if (shift)
				{
					locked.cHealth = int(*(float*)(shift + 0x8));
					locked.mHealth = int(*(float*)(shift + 0xC));
				}
				if (locked.mHealth > 0)
					locked.pHealth = int(100.f * float(locked.cHealth) / float(locked.mHealth));
				else
					locked.pHealth = 0;
				//locked.lvl = ch.GetScaledLevel();
				//locked.lvlActual = ch.GetLevel();
			}
			else if (agType == GW2::AGENT_TYPE_GADGET_ATTACK_TARGET) // world boss
			{
				locked.valid = true;
				locked.id = ag.GetAgentId();
				locked.type = agType;

				locked.pos = ag.GetPos();

				unsigned long shift = *(unsigned long*)ag.m_ptr;
				shift = *(unsigned long*)(shift + 0x30);
				shift = *(unsigned long*)(shift + 0x28);
				shift = *(unsigned long*)(shift + 0x17c);
				if (shift)
				{
					locked.cHealth = int(*(float*)(shift + 0x8));
					locked.mHealth = int(*(float*)(shift + 0xC));
				}
				if (locked.mHealth > 0)
					locked.pHealth = int(100.f * float(locked.cHealth) / float(locked.mHealth));
				else
					locked.pHealth = 0;
				//locked.lvl = ch.GetScaledLevel();
				//locked.lvlActual = ch.GetLevel();
			}

			if (locked.cHealth == 0 && locked.mHealth != 78870) // don't clear if 78870 (indestructible golem) or targetLocked
			{
				if (targetLock)
					locked.alive = false;
				else
					locked = {};
			}
		}

		// Floaters
		if (floatAllyNpc || floatEnemyNpc || floatAllyPlayer || floatEnemyPlayer || floatSiege)
		{
			int agType = ag.GetType();

			// NPC & Player
			if (agType == GW2::AGENT_TYPE_CHAR)
			{
				Character ch = ag.GetCharacter();

				// gather data
				Vector3 pos = ag.GetPos();
				int cHealth = int(ch.GetCurrentHealth());
				int mHealth = int(ch.GetMaxHealth());
				int attitude = ch.GetAttitude();
				int prof = ch.GetProfession();

				// Filter the dead
				if (cHealth > 0 && mHealth > 1)
				{
					// Filter those out of range
					if (Dist(self.pos, pos) <= floatRadius)
					{
						Float floater;
						floater.pos = pos;
						floater.mHealth = mHealth;
						floater.prof = prof;

						// player vs npc
						if (ch.IsPlayer() && !ch.IsControlled()) // (ignore self)
						{
							// allyPlayer
							if (floatAllyPlayer && attitude == GW2::ATTITUDE_FRIENDLY)
								floaters.allyPlayer.push_back(floater);

							// enemyPlayer
							if (floatEnemyPlayer && attitude == GW2::ATTITUDE_HOSTILE)
								floaters.enemyPlayer.push_back(floater);
						}

						if (!ch.IsPlayer()){
							// allyNpc
							if (floatAllyNpc && (attitude == GW2::ATTITUDE_FRIENDLY || attitude == GW2::ATTITUDE_NEUTRAL))
								floaters.allyNpc.push_back(floater);

							// enemyNpc
							if (floatEnemyNpc && (attitude == GW2::ATTITUDE_HOSTILE || attitude == GW2::ATTITUDE_INDIFFERENT))
								floaters.enemyNpc.push_back(floater);
						}
					}
				}
			}
		}

		// Allies list
		if (alliesList) {
			Character ch = ag.GetCharacter();

			// collect only valid allies (and yourself)
			bool chValid = true;

			if (!ch.IsValid())
				chValid = false;

			//if (ch.IsControlled())
			//chValid = false;

			if (!ch.IsPlayer() || ch.GetAttitude() != GW2::ATTITUDE_FRIENDLY)
				chValid = false;

			// gather char data
			if (chValid){
				Ally ally;
				ally.id = ag.GetAgentId();

				ally.profession = ch.GetProfession();
				ally.mHealth = int(round(ch.GetMaxHealth() / (100 + wvwBonus) * 100));
				//ally.cHealth = int(ch.GetCurrentHealth());
				//if (ally.mHealth > 0)
				//ally.pHealth = int(100.f * float(ally.cHealth) / float(ally.mHealth));
				//else
				//ally.pHealth = 0;
				ally.lvl = ch.GetScaledLevel();
				ally.lvlActual = ch.GetLevel();
				ally.name = ch.GetName();

				baseHpReturn base = baseHp(ally.lvl, ally.profession);
				ally.vitality = int(round((ally.mHealth - base.health) / 10));
				ally.traits = (926.f / base.vitality) * ((ally.mHealth - base.health) / 100.f / 5.f);
				ally.traits = round(ally.traits * 10) / 10; // round to 0.0

				switch (ally.profession)
				{
				case GW2::PROFESSION_WARRIOR:
					allies.war.push_back(ally);
					break;
				case GW2::PROFESSION_NECROMANCER:
					allies.necro.push_back(ally);
					break;

				case GW2::PROFESSION_ENGINEER:
					allies.engi.push_back(ally);
					break;
				case GW2::PROFESSION_RANGER:
					allies.ranger.push_back(ally);
					break;
				case GW2::PROFESSION_MESMER:
					allies.mes.push_back(ally);
					break;

				case GW2::PROFESSION_GUARDIAN:
					allies.guard.push_back(ally);
					break;
				case GW2::PROFESSION_THIEF:
					allies.thief.push_back(ally);
					break;
				case GW2::PROFESSION_ELEMENTALIST:
					allies.ele.push_back(ally);
					break;
				}
			}
		}

		// Displacement
		if (logDisplacement)
		{
			if (logDisplacementEnemy)
			{
				if (locked.valid) {
					if (locked.id != bufferDisplacement.id || (bufferDisplacement.start.x == 0 && bufferDisplacement.start.y == 0 && bufferDisplacement.start.z == 0))
					{
						bufferDisplacement.start = locked.pos;
						bufferDisplacement.id = locked.id;
					}
					else
					{
						float displacement = Dist(bufferDisplacement.start, locked.pos);
						bufferDisplacement.dist = int(displacement);
					}
				}
				else
				{
					// reset
					bufferDisplacement = {};
				}
			}
			else
			{
				if (bufferDisplacement.start.x == 0 && bufferDisplacement.start.y == 0 && bufferDisplacement.start.z == 0)
				{
					bufferDisplacement.start = self.pos;
				}
				else
				{
					float displacement = Dist(bufferDisplacement.start, self.pos);
					bufferDisplacement.dist = int(displacement);
				}
			}
		}
		else
		{
			// reset
			bufferDisplacement = {};
		}
	}

	// Bottom Element //
	{
		stringstream ss;
		StrInfo strInfo;

		if (selfHealthPercent && self.alive)
		{
			ss << format("%i") % self.pHealth;

			strInfo = StringInfo(ss.str());
			float x = round(aBottom.x - strInfo.x / 2);
			float y = round(aBottom.y - lineHeight);

			//DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
			//DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
			font.Draw(x, y, fontColor, ss.str());
		}
	}

	// Left Element //
	{
		if (alliesList)
		{
			stringstream ss;
			stringstream sp;
			stringstream sn;
			stringstream sh;
			stringstream sv;
			stringstream st;


			ss << format("Nearby Ally Players (WvW HP Bonus: %i%s)") % wvwBonus % "%%";
			sp << format("Class");
			sn << format("Name");
			sh << format("Health");
			sv << format("Vitality");
			st << format("Traits");

			bool listEmpty = true;
			if (!allies.war.empty())
			{
				for (auto & ally : allies.war) {
					sp << format("\nWar:");
					sn << format("\n%s") % ally.name;
					sh << format("\n%i hp") % ally.mHealth;
					sv << format("\n%+i") % ally.vitality;
					st << format("\n%+.1f") % ally.traits;
				}
				listEmpty = false;
			}
			if (!allies.guard.empty())
			{
				for (auto & ally : allies.guard) {
					sp << format("\nGuard:");
					sn << format("\n%s") % ally.name;
					sh << format("\n%i hp") % ally.mHealth;
					sv << format("\n%+i") % ally.vitality;
					st << format("\n%+.1f") % ally.traits;
				}
				listEmpty = false;
			}

			if (!allies.ele.empty())
			{
				for (auto & ally : allies.ele) {
					sp << format("\nEle:");
					sn << format("\n%s") % ally.name;
					sh << format("\n%i hp") % ally.mHealth;
					sv << format("\n%+i") % ally.vitality;
					st << format("\n%+.1f") % ally.traits;
				}
				listEmpty = false;
			}
			if (!allies.mes.empty())
			{
				for (auto & ally : allies.mes) {
					sp << format("\nMes:");
					sn << format("\n%s") % ally.name;
					sh << format("\n%i hp") % ally.mHealth;
					sv << format("\n%+i") % ally.vitality;
					st << format("\n%+.1f") % ally.traits;
				}
				listEmpty = false;
			}

			if (!allies.thief.empty())
			{
				for (auto & ally : allies.thief) {
					sp << format("\nThief:");
					sn << format("\n%s") % ally.name;
					sh << format("\n%i hp") % ally.mHealth;
					sv << format("\n%+i") % ally.vitality;
					st << format("\n%+.1f") % ally.traits;
				}
				listEmpty = false;
			}
			if (!allies.ranger.empty())
			{
				for (auto & ally : allies.ranger) {
					sp << format("\nRanger:");
					sn << format("\n%s") % ally.name;
					sh << format("\n%i hp") % ally.mHealth;
					sv << format("\n%+i") % ally.vitality;
					st << format("\n%+.1f") % ally.traits;
				}
				listEmpty = false;
			}
			if (!allies.engi.empty())
			{
				for (auto & ally : allies.engi) {
					sp << format("\nEngi:");
					sn << format("\n%s") % ally.name;
					sh << format("\n%i hp") % ally.mHealth;
					sv << format("\n%+i") % ally.vitality;
					st << format("\n%+.1f") % ally.traits;
				}
				listEmpty = false;
			}
			if (!allies.necro.empty())
			{
				for (auto & ally : allies.necro) {
					sp << format("\nNecro:");
					sn << format("\n%s") % ally.name;
					sh << format("\n%i hp") % ally.mHealth;
					sv << format("\n%+i") % ally.vitality;
					st << format("\n%+.1f") % ally.traits;
				}
				listEmpty = false;
			}
			if (listEmpty)
			{
				sp << format("\n...");
				sn << format("\n...");
				sh << format("\n...");
				sv << format("\n...");
				st << format("\n...");
			}


			// CharName max width
			stringstream sx;
			sx << "WWWWWWWWWWWWWWWWWWW";
			StrInfo strInfo;
			strInfo = StringInfo(sx.str());

			float spOffset = 0;
			float snOffset = spOffset + 65;
			float shOffset = snOffset + strInfo.x;
			float svOffset = shOffset + 85;
			float stOffset = svOffset + 70;
			float sxOffset = stOffset + 60;

			float x = round(aLeft.x);
			float y = round(aLeft.y);

			strInfo = StringInfo(sp.str());
			int lineCount = int(strInfo.lineCount) + 2;

			// render the list
			DrawRectFilled(x - padX, y - padY, sxOffset + padX * 2, float(lineCount * lineHeight) + padY * 2, backColor - 0x22000000);
			DrawRect(x - padX, y - padY, sxOffset + padX * 2, float(lineCount * lineHeight) + padY * 2, borderColor);

			int lineShiftY = 2;
			for (int i = 3; i < lineCount; i++) {
				DrawLine(x - padX, y - padY + i * lineHeight + lineShiftY, x + sxOffset + padX, y - padY + i * lineHeight + lineShiftY, borderColor);
			}
			font.Draw(x + spOffset, y, fontColor, ss.str()); y += 2 * lineHeight;
			font.Draw(x + spOffset, y, fontColor, sp.str());
			font.Draw(x + snOffset, y, fontColor, sn.str());
			font.Draw(x + shOffset, y, fontColor, sh.str());
			font.Draw(x + svOffset, y, fontColor, sv.str());
			font.Draw(x + stOffset, y, fontColor, st.str());
		}
	}

	// TopLeft Element //
	{
		if (targetSelected)
		{
			if (targetLock && selected.valid && locked.valid && selected.id == locked.id)
			{

				stringstream ss;
				StrInfo strInfo;

				ss << format("Selected & Locked: %i / %i [%i%s]") % selected.cHealth % selected.mHealth % selected.pHealth % "%%";

				strInfo = StringInfo(ss.str());
				float x = round(aTopLeft.x - strInfo.x / 2);
				float y = round(aTopLeft.y);

				DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
				DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
				font.Draw(x, y, fontColor, ss.str());

				// Prepare for Next Element
				aTopLeft.y += strInfo.lineCount * lineHeight + padY * 2;
			}
			else
			{
				if (selected.valid)
				{
					stringstream ss;
					StrInfo strInfo;

					ss << format("Selected: %i / %i [%i%s]") % selected.cHealth % selected.mHealth % selected.pHealth % "%%";

					strInfo = StringInfo(ss.str());
					float x = round(aTopLeft.x - strInfo.x / 2);
					float y = round(aTopLeft.y);

					DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
					DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
					font.Draw(x, y, fontColor, ss.str());

					// Prepare for Next Element
					aTopLeft.y += strInfo.lineCount * lineHeight + padY * 2;
				}

				if (targetLock && locked.valid)
				{
					stringstream ss;
					StrInfo strInfo;

					ss << format("Locked: %i / %i [%i%s]") % locked.cHealth % locked.mHealth % locked.pHealth % "%%";

					strInfo = StringInfo(ss.str());
					float x = round(aTopLeft.x - strInfo.x / 2);
					float y = round(aTopLeft.y);

					DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
					DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
					font.Draw(x, y, fontColor, ss.str());

					// Prepare for Next Element
					aTopLeft.y += strInfo.lineCount * lineHeight + padY * 2;
				}
			}

			if (targetInfo && selected.valid)
			{
				//aTopLeft.y += lineHeight;

				stringstream ss;
				StrInfo strInfo;

				if (targetInfoAlt)
				{
					if (agLocked.GetType() == GW2::AGENT_TYPE_CHAR)
					{
						int stats[7] {};
						stats[0] = 0; // power
						stats[1] = 0; // precision
						stats[2] = 0; // toughness
						stats[3] = 0; // vitality
						stats[4] = 0; // ferocity
						stats[5] = 0; // healing
						stats[6] = 0; // condition

						unsigned long shift;
						shift = *(unsigned long*)agLocked.m_ptr;
						shift = *(unsigned long*)(shift + 0x30);
						shift = *(unsigned long*)(shift + 0x138);

						stats[0] = *(unsigned long*)(shift + 0x18c + 0x4 * 0);
						stats[1] = *(unsigned long*)(shift + 0x18c + 0x4 * 1);
						stats[2] = *(unsigned long*)(shift + 0x18c + 0x4 * 2);
						stats[3] = *(unsigned long*)(shift + 0x18c + 0x4 * 3);
						stats[4] = *(unsigned long*)(shift + 0x18c + 0x4 * 4);
						stats[5] = *(unsigned long*)(shift + 0x18c + 0x4 * 5);
						stats[6] = *(unsigned long*)(shift + 0x18c + 0x4 * 6);

						ss << format("Power - %i") % stats[0];
						ss << format("\nPrecision - %i") % stats[1];
						ss << format("\nToughness - %i") % stats[2];
						ss << format("\nVitality - %i") % stats[3];
						ss << format("\nFerocity - %i") % stats[4];
						ss << format("\nHealing - %i") % stats[5];
						ss << format("\nCondition - %i") % stats[6];

						ss << format("\n");
						ss << format("\n(Agent: %p)") % (void**)agLocked.m_ptr;
					}
				}
				else
				{
					ss << format("Distance: %i") % int(Dist(self.pos, selected.pos));
				}

				strInfo = StringInfo(ss.str());
				float x = round(aTopLeft.x - strInfo.x / 2);
				float y = round(aTopLeft.y);

				DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
				DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
				font.Draw(x, y, fontColor, ss.str());

				// Prepare for Next Element
				ss.str("");
				aTopLeft.y += strInfo.lineCount * lineHeight + padY * 2;
			}
		}
	}

	// Top Elements (and floaters) //
	{
		if (floatAllyNpc || floatEnemyNpc || floatAllyPlayer || floatEnemyPlayer || floatSiege)
		{
			stringstream ss;
			StrInfo strInfo;

			ss << format("R: %i") % floatRadius;

			if (floatAllyNpc)
				ss << format(" | AllyNPCs: %i") % floaters.allyNpc.size();

			if (floatEnemyNpc)
				ss << format(" | FoeNPCs: %i") % floaters.enemyNpc.size();

			if (floatAllyPlayer)
				ss << format(" | Allies: %i") % floaters.allyPlayer.size();

			if (floatEnemyPlayer)
				ss << format(" | Foes: %i") % floaters.enemyPlayer.size();

			if (floatSiege)
				ss << format(" | Siege: %i") % floaters.siege.size();

			strInfo = StringInfo(ss.str());
			float x = round(aTop.x - strInfo.x / 2);
			float y = round(aTop.y);

			DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
			DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
			font.Draw(x, y, fontColor - (floatCircles ? 0x00aa0000 : 0), ss.str());

			aTop.y += strInfo.y + padY * 2;

			if (floatAllyPlayerProf)
			{
				int prof[10] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
				for (auto & ally : floaters.allyPlayer) {
					prof[ally.prof]++;
				}

				ss.str("");
				ss << format("War: %i") % prof[2];
				ss << format(" | Guard: %i") % prof[1];
				ss << format(" | Ele: %i") % prof[6];
				ss << format(" | Thief: %i") % prof[5];
				ss << format(" | Mes: %i") % prof[7];
				ss << format(" | Engi: %i") % prof[3];
				ss << format(" | Ranger: %i") % prof[4];
				ss << format(" | Necro: %i") % prof[8];

				strInfo = StringInfo(ss.str());
				float x = round(aTop.x - strInfo.x / 2);
				float y = round(aTop.y);

				DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
				DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
				font.Draw(x, y, fontColor - (floatCircles ? 0x00aa0000 : 0), ss.str());

				aTop.y += strInfo.y + padY * 2;
			}


			if (floatCircles)
			{
				float x, y;
				if (floatAllyNpc && floaters.allyNpc.size() > 0)
				{
					for (auto & floater : floaters.allyNpc) {
						if (WorldToScreen(floater.pos, &x, &y))
						{
							stringstream fs;
							if (floatType)
								fs << format("%i") % int(Dist(self.pos, floater.pos));
							else
								fs << format("%i") % floater.mHealth;

							StrInfo fsInfo = StringInfo(fs.str());
							font.Draw(x - fsInfo.x / 2, y - 15, fontColor, fs.str());

							DWORD color = 0x4433ff00;
							DrawCircleProjected(floater.pos, 20.0f, color);
							DrawCircleFilledProjected(floater.pos, 20.0f, color - 0x30000000);
						}
					}
				}

				if (floatEnemyNpc && floaters.enemyNpc.size() > 0)
				{
					for (auto & floater : floaters.enemyNpc) {
						if (WorldToScreen(floater.pos, &x, &y))
						{
							stringstream fs;
							if (floatType)
								fs << format("%i") % int(Dist(self.pos, floater.pos));
							else
								fs << format("%i") % floater.mHealth;

							StrInfo fsInfo = StringInfo(fs.str());
							font.Draw(x - fsInfo.x / 2, y - 15, fontColor, fs.str());

							DWORD color = 0x44ff3300;
							DrawCircleProjected(floater.pos, 20.0f, color);
							DrawCircleFilledProjected(floater.pos, 20.0f, color - 0x30000000);
						}
					}
				}

				if (floatAllyPlayer && floaters.allyPlayer.size() > 0)
				{
					for (auto & floater : floaters.allyPlayer) {
						if (WorldToScreen(floater.pos, &x, &y))
						{
							stringstream fs;
							if (floatType)
								fs << format("%i") % int(Dist(self.pos, floater.pos));
							else
								fs << format("%i") % floater.mHealth;

							StrInfo fsInfo = StringInfo(fs.str());
							font.Draw(x - fsInfo.x / 2, y - 15, fontColor, fs.str());

							DWORD color = 0x4433ff00;
							DrawCircleProjected(floater.pos, 20.0f, color);
							DrawCircleFilledProjected(floater.pos, 20.0f, color - 0x30000000);
						}
					}
				}

				if (floatEnemyPlayer && floaters.enemyPlayer.size() > 0)
				{
					for (auto & floater : floaters.enemyPlayer) {
						if (WorldToScreen(floater.pos, &x, &y))
						{
							stringstream fs;
							if (floatType)
								fs << format("%i") % int(Dist(self.pos, floater.pos));
							else
								fs << format("%i") % floater.mHealth;

							StrInfo fsInfo = StringInfo(fs.str());
							font.Draw(x - fsInfo.x / 2, y - 15, fontColor, fs.str());

							DWORD color = 0x44ff3300;
							DrawCircleProjected(floater.pos, 20.0f, color);
							DrawCircleFilledProjected(floater.pos, 20.0f, color - 0x30000000);
						}
					}
				}

				if (floatSiege && floaters.siege.size() > 0)
				{
					for (auto & floater : floaters.siege) {
						//DWORD color = 0x44ff3300;
						//DrawCircleProjected(floater.pos, 20.0f, color);
						//DrawCircleFilledProjected(floater.pos, 20.0f, color - 0x30000000);
					}
				}
			}
		}

		if (logSpeedometer) {
			stringstream ss;
			StrInfo strInfo;

			ss << format("Speed: ");

			if (!bufferSpeedometer.empty())
			{
				double average[2] {};
				size_t samples = 0;

				// Speed ~ .5s
				samples = 5;
				if (samples > bufferSpeedometer.size())
					samples = bufferSpeedometer.size();
				average[0] = 0;
				for (size_t i = 0; i < samples; i++)
					average[0] += bufferSpeedometer[i];
				average[0] = average[0] / samples * (1000 / 100);

				// Speed ~ 3s
				samples = 30;
				if (samples > bufferSpeedometer.size())
					samples = bufferSpeedometer.size();
				average[1] = 0;
				for (size_t i = 0; i < samples; i++)
					average[1] += bufferSpeedometer[i];
				average[1] = average[1] / samples * (1000 / 100);

				// Prepare String
				ss << format("%i in/s, %i in/s") % int(average[0]) % int(average[1]);
			}
			else
			{
				ss << format("0 in/s, 0 in/s");
			}

			strInfo = StringInfo(ss.str());
			float x = round(aTop.x - strInfo.x / 2);
			float y = round(aTop.y);

			DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
			DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
			font.Draw(x, y, fontColor - (logSpeedometerEnemy ? 0x00aa0000 : 0), ss.str());

			aTop.y += strInfo.y + padY * 2;
		}

		if (logDisplacement)
		{
			stringstream ss;
			StrInfo strInfo;

			ss << format("Distance: %i") % bufferDisplacement.dist;

			strInfo = StringInfo(ss.str());
			float x = round(aTop.x - strInfo.x / 2);
			float y = round(aTop.y);

			DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
			DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
			font.Draw(x, y, fontColor - (logDisplacementEnemy ? 0x00aa0000 : 0), ss.str());

			aTop.y += strInfo.y + padY * 2;

		}
		else
		{
			if (logDisplacementStart.x != 0 || logDisplacementStart.y != 0 || logDisplacementStart.z != 0)
				logDisplacementStart = Vector3(0, 0, 0);
		}
	}

	// TopRight Elements //
	{
		if (logDps)
		{
			// separate ss vars
			stringstream ss;
			StrInfo strInfo;

			float aAdjustX = 120; // adjust anchor -120

			if (!bufferDps.empty())
			{
				double average[6] {}; // for 1s & 5s
				size_t samples = 0;

				// DP1s
				samples = 4; // 1s/250ms=4
				if (samples > bufferDps.size())
					samples = bufferDps.size();
				average[1] = 0;
				for (size_t i = 0; i < samples; i++)
					average[1] += bufferDps[i];
				average[1] = average[1] / samples * (1000 / 250);

				// DP5s
				samples = 20; // 5s/250ms=20
				if (samples > bufferDps.size())
					samples = bufferDps.size();
				average[5] = 0;
				for (size_t i = 0; i < samples; i++)
					average[5] += bufferDps[i];
				average[5] = average[5] / samples * (1000 / 250);

				// Prepare String
				ss << format("DP1s: %0.0f\n") % average[1];
				ss << format("DP5s: %0.0f\n") % average[5];
				if (logDpsDetails)
				{
					for (size_t i = 0; i < bufferDps.size(); i++)
						ss << format("\nDP250ms: %i") % bufferDps[i];
				}
			}
			else
			{
				ss << format("DP1s: ...\n");
				ss << format("DP5s: ...");
			}

			strInfo = StringInfo(ss.str());
			if (logDpsDetails && !bufferDps.empty() && strInfo.x < aAdjustX)
				strInfo.x = aAdjustX; // box min-width with history stream
			float x = round(aTopRight.x - aAdjustX / 2); // perma anchor offset
			float y = round(aTopRight.y);

			// Draw
			DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
			DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
			font.Draw(x, y, fontColor, ss.str());

			// Prepare for Next Element
			//ss.str("");
			//aTopRight.y += strInfo.lineCount * lineHeight + padY * 2;
			aTopRight.x -= aAdjustX / 2 + padX + 2;
		}

		if (logKillTimer)
		{
			// separate ss vars
			stringstream ss;
			StrInfo strInfo;

			// Prepare String
			if (bufferKillTimer.time > 0)
			{
				ss << format("Timer: %s") % SecondsToString(bufferKillTimer.time);
				if (logKillTimerDetails)
					ss << format("\nDPS: %0.2f") % bufferKillTimer.dps;
			}
			else
			{
				ss << format("Timer: 0.0s");
				if (logKillTimerDetails)
					ss << format("\nDPS: 0.0");
			}

			strInfo = StringInfo(ss.str());
			float x = 0;
			float y = round(aTopRight.y);
			if (logDps)
				x = round(aTopRight.x - strInfo.x - padX); // perma anchor offset with logDps
			else
				x = round(aTopRight.x - strInfo.x / 2); // center otherwise


			// Draw
			DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
			DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
			font.Draw(x, y, fontColor, ss.str());

			// Prepare for Next Element
			//ss.str("");
			aTopRight.y += strInfo.lineCount * lineHeight + padY * 2;
			//aTopRight.x -= 0;
		}

	}

	// Right Elements //
	{
		if (logAttackRate)
		{
			stringstream ss;
			StrInfo strInfo;

			if (logAttackRateToFile)
				ss << format("� Recording �\n");
			else
				ss << format("� Monitoring �\n");
			ss << format("� Attack Rate �\n");
			ss << format("\n");

			if (!bufferAttackRate.empty())
			{
				//double min = *min_element(bufferAttackRate.begin(), bufferAttackRate.end());
				//double max = *max_element(bufferAttackRate.begin(), bufferAttackRate.end());
				double average = 0;
				for (size_t i = 0; i < bufferAttackRate.size(); i++)
					average += bufferAttackRate[i];
				average = average / bufferAttackRate.size();

				ss << format("Counter: %i\n") % threadAttackRateCounter;
				//ss << format("Min: %0.3fs\n") % min;
				ss << format("Average: %0.3fs\n") % average;
				//ss << format("Max: %0.3fs\n") % max;

				if (logAttackRateDetails)
				{
					ss << format("\n");
					ss << format("History\n");
					for (size_t i = 0; i < bufferAttackRate.size(); i++)
						ss << format("� %0.3fs\n") % bufferAttackRate[i];
				}
			}
			else
			{
				ss << format("Counter: ...\n");
				//ss << format("Minimum: ...\n");
				ss << format("Average: ...\n");
				//ss << format("Maximum: ...\n");

				if (logAttackRateDetails)
				{
					ss << format("\n");
					ss << format("History\n");
					ss << format("� ...\n");
				}
			}
			ss << format("\n");
			ss << format("Threshold: %i hits\n") % AttackRateChainHits;

			strInfo = StringInfo(ss.str());

			float aAdjustX = 120; // adjust anchor -120
			if (strInfo.x < aAdjustX)
				strInfo.x = aAdjustX; // perma box min-width
			float x = round(aRight.x - strInfo.x);
			float y = round(aRight.y);

			// Draw
			DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
			DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
			font.Draw(x, y, fontColor - (logAttackRateToFile ? 0x00aa0000 : 0), ss.str());

			// Prepare for Next Element
			//ss.str("");
			//aTopRight.y += strInfo.lineCount * lineHeight + padY * 2;
			aRight.x = x - padX * 2 - 5;
		}

		if (logHits)
		{
			stringstream ss;
			StrInfo strInfo;

			if (logHitsToFile)
				ss << format("� Recording �\n");
			else
				ss << format("� Monitoring �\n");

			ss << format("� Damage Hits �\n");
			ss << format("\n");

			if (!bufferHits.empty())
			{
				//double min = *min_element(bufferHits.begin(), bufferHits.end());
				//double max = *max_element(bufferHits.begin(), bufferHits.end());
				double average = 0;
				for (size_t i = 0; i < bufferHits.size(); i++)
					average += bufferHits[i];
				average = average / bufferHits.size();

				ss << format("Counter: %i\n") % threadHitsCounter;
				ss << format("Average: %0.1f\n") % average;

				if (logHitsDetails)
				{
					ss << format("\n");
					ss << format("History\n");
					for (size_t i = 0; i < bufferHits.size(); i++)
						ss << format("� %i\n") % bufferHits[i];
				}
			}
			else
			{
				ss << format("Counter: ...\n");
				ss << format("Average: ...\n");

				if (logHitsDetails)
				{
					ss << format("\n");
					ss << format("History\n");
					ss << format("� ...\n");
				}
			}

			strInfo = StringInfo(ss.str());


			float aAdjustX = 120; // adjust anchor -120
			if (strInfo.x < aAdjustX)
				strInfo.x = aAdjustX; // perma box min-width
			float x = round(aRight.x - strInfo.x);
			float y = round(aRight.y);

			// Draw
			DrawRectFilled(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, backColor - 0x22000000);
			DrawRect(x - padX, y - padY, strInfo.x + padX * 2, strInfo.y + padY * 2, borderColor);
			font.Draw(x, y, fontColor - (logHitsToFile ? 0x00aa0000 : 0), ss.str());

			// Prepare for Next Element
			//ss.str("");
			//aTopRight.y += strInfo.lineCount * lineHeight + padY * 2;
			aRight.x = x - padX * 2 - 5;
		}
	}
}

void GW2LIB::gw2lib_main()
{
	locale::global(locale("en-US"));

    EnableEsp(ESP);
	thread t1(&threadHotKeys);
	thread t2(&threadDps);
	thread t3(&threadKillTimer);
	thread t4(&threadHits);
	thread t5(&threadAttackRate);
	thread t6(&threadSpeedometer);

	if (!font.Init(lineHeight, "Verdana"))
    {
        //DbgOut("could not create font");
        return;
    }

	// wait for exit hotkey
	while (GetAsyncKeyState(VK_F12) >= 0)
        ;
	
	// self destruct sequence
	t1.interrupt(); //t1.join();
	t2.interrupt(); //t2.join();
	t3.interrupt(); //t3.join();
	t4.interrupt(); //t4.join();
	t5.interrupt(); //t5.join();
	t6.interrupt(); //t6.join();
	Sleep(1000);
	return;
}