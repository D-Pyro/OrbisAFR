# OrbisAFR
Orbis (PS4) Application File Redirector

OrbisAFR is a payload for editing in-game files easily.
Add Skyrim mods, Minecraft textures or any other asset without re-building PKG !

The principle is simple, all new (or replaced) data is stored in /data

## Example
For example, I want to edit the intro of Black Ops 3
The intro video is here:

    /mnt/sandbox/CUSA02624_000/app0/intro/bo3_global_logo_logosequence.mkv

I have just to upload a new .mkv in 

    /data/CUSA02624/app0/intro/bo3_global_logo_logosequence.mkv

Now if OrbisAFP is loaded, the .mkv gets loaded from /data and not /mnt/sandbox/... !

All files added in `/data/CUSA02624/` are like files in `/mnt/sandbox/CUSA02624_000/`

- If the file exists in `/data/CUSA02624/` and in `/mnt/sandbox/CUSA02624_000/`, the file in data is used
- If the file doesn't exist in `/data/CUSA02624/`, OrbisAFR uses original file from `/mnt/sandbox/CUSA02624_000/`
- If the file exists in `/data/CUSA02624/` and not in `/mnt/sandbox/CUSA02624_000/`, the file in data is used

OrbisAFR doesn't just replace, but can also add new files in a game !