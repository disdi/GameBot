#include "objects.h"
#include "cutouts.h"
#include <QString>
#include <QPoint>

// F for "feature"
// use for all props that are not moving & tied to the level grid
// name - handle to refer to feature in code
// humanName - name for debugging
// sprite - sprite list, see below
// tiles - size in tiles (both dimensions assumed equal)
// type - building type class, see objects.h
#define _F(name, humanName, sprite, count, type) \
    std::pair<const QString, const FeatureDesc> \
        (name, \
         FeatureDesc(sprite, humanName, count, type))

// S for "sprites"
// The sprite list contains multiple ways in which the same feature may be detected (FIXME: allow overlapping).
// List contains multiple I entries

// I for "Image"
// path - path to image file relative to qrc:/cutouts/
// threshold - detection threshold
// anchor - QPoint [alias pos] for pixel difference (top tile top corner - image top-left corner)
#define _I(path, position, threshold) {QString(":/cutouts/") + path, position, threshold}
typedef SpriteDescAlts _S;
typedef QPoint pos;

// SINGLE can replace S when detection doesn't need multiple images
#define _SINGLE(path, position, threshold) _S({_I(path, position, threshold)})

// VERY IMPORTANT: all images must be cut out from the same scale; currently 1920x1200 default zoom
// ALSO IMPORTANT: UI may not scale proportionally to map features, keep in separate FeatureList
// Make sure the images are regular RGB(A) with 8-bit depth


const FeatureDescList cutouts {
    _F("TH10",  "TownHall10",    _SINGLE("TH10.png",             pos(25, 12),   0.9),   1, new Building(4, 5500)),
    //_F("AD8",   "AirDefense8",  _SINGLE("defense/ad8.png",      pos(17, -8),    0.8),   0,  3, Defense(1170, 10, 320, Defense::SINGLE, Defense::AIR)),
    _F("CC6",   "ClanCastle6",   _SINGLE("cc6.png",              pos(20, -18),  0.9),   1, new Building(3, 0)),

    _F("TR0",   "Tree",          _SINGLE("props/TR0.png",        pos(20, -15),  0.95),  0, new Scenery(2)),
    _F("SH0",   "Shed",          _SINGLE("props/sh0.png",        pos(20, -3),   0.95),  0, new Scenery(2)),

    _F("AC8",   "ArmyCamp8",     _SINGLE("army/ac8.png",         pos(18, -90),  0.95),  0, new Building(5, 0)),
    _F("DF3",   "DarkFactory3",  _SINGLE("army/df3.png",         pos(8, -46),   0.95),  0, new Building(3, 0)),
    _F("LA8",   "Laboratory8",   _SINGLE("army/la8.png",         pos(48, -23),  0.95),  0, new Building(4, 0)),
    _F("BA10",  "Barracks10",    _SINGLE("army/ba10.png",        pos(32, 2),    0.95),  0, new Building(3, 0)),
    _F("DB6",   "DarkBarracks6", _SINGLE("army/db6.png",         pos(23, 22),   0.95),  0, new Building(3, 0)),

    _F("BK",    "BKingLair",     _SINGLE("army/bk.png",          pos(17, -11),  0.95),  1, new Building(3, 0)), // Special: has range
    _F("AQ",    "ArcherQueen",   _SINGLE("army/aq.png",          pos(21, -18),  0.95),  1, new Building(3, 0)), // Special: has range

    _F("AD8",   "AirDefense8",   _SINGLE("defense/ad8_m.png",    pos(30, 27),   0.8),   0, new Defense(3, 1170, 10, 320, Defense::SINGLE, Defense::AIR)), // alpha mask
    _F("AS4",   "AirSweeper4",   _SINGLE("defense/as4.png",      pos(20, -14),  0.92),  0, new Defense(2, 0, 15, 36, Defense::PUSH, Defense::AIR)), // It can be rotated 45 degrees at a time, and hence has 8 rigid directional settings. The Air Sweeper attacks in a rectangular area of effect of width 5 tiles and length 14. (http://clashofclans.wikia.com/wiki/Air_Sweeper)
            // damage is push_tiles * 10 over 5 seconds
            // TODO: decrease threshold to ~0.9 after UI is masked out to gain obscured detection
    _F("CA13",  "Cannon13",      _SINGLE("defense/ca13_2.png",   pos(38, -32),  0.92), 0,  new Defense(3, 0, 9, 98, Defense::SINGLE, Defense::GROUND)),
    _F("WT8",   "Wizard8",       _SINGLE("defense/wt8.png",      pos(23, -10),  0.95),  0, new Defense(3, 0, 7, 48, Defense::SPLASH1TILE, Defense::AIR | Defense::GROUND)),
    _F("AT13",  "Archer13",      _SINGLE("defense/at13.png",     pos(21, -2),   0.95),  0, new Defense(3, 0, 10, 98, Defense::SINGLE, Defense::AIR | Defense::GROUND)),
    _F("MO8",   "Mortar8",       _SINGLE("defense/mo8.png",      pos(5, -35),   0.95),  0, new Defense(3, 0, 11, 13, Defense::SPLASH15TILE, Defense::GROUND)), // FIXME: range is <4, 11>
    _F("XB4" ,  "XBow4",         _SINGLE("defense/xb4_2.png",    pos(39, -32),  0.95), 0,  new Defense(3, 0, 11, 80, Defense::SINGLE, Defense::AIR | Defense::GROUND)), // FIXME: also Range=14, AIR, depending on setting
            // TODO: decrease threshold to ~0.9 after UI masked out
    _F("IT3",   "Inferno3",      _SINGLE("defense/it3.png",      pos(20, 16),   0.95),  0, new Defense(2, 0, 9, 140, Defense::SINGLE, Defense::AIR | Defense::GROUND)), // TODO: encoding the damage... it's complicated

    _F("EC12",  "ElixirColl12",  _SINGLE("storage/ec12.png",     pos(5, 14),    0.95),  0, new Building(3, 0)),
    _F("DD6",   "DarkDrill6",    _S({_I("storage/dd6.png",      pos(-9, -14),   0.97),
                                     _I("storage/dd6_1.png",    pos(-8, -17),   0.95)}), 0, new Building(3, 0)),
    _F("GM12",  "GoldMine12",    _SINGLE("storage/gm12.png",    pos(30, -19),   0.95),  0, new Building(3, 0)),

    _F("GS11-0","GoldStor11",   _SINGLE("storage/gold11base.png",pos(12, 12),   0.95),  0, new Storage(3, 0, Storage::GOLD, 0)), // FIXME: health, offset, amount
    _F("DS6-0", "DarkStor6_0",   _SINGLE("storage/ds6-0.png",    pos(16, -9),   0.95),  0, new Storage(3, 0, Storage::DARK, 0)), // FIXME: health, offset, amount
    _F("ES11-0","ElixirStor11_0",_SINGLE("storage/es11-0.png",   pos(0, 0),     0.95),  0, new Storage(3, 0, Storage::ELIXIR, 0)), // FIXME: health, offset, amount
};

