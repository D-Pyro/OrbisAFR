# OrbisAFR
Orbis (PS4) Application File Redirector

OrbisAFR is a payload for edit in-game file easily.
Add Skyrim mods, Minecraft texture or any other things without re-buid PKG !

The principe is simple, all new (or replace) data is stocked in /data

## Example
For example, i want to edit the intro of Black Ops 3
The introduction is here:

    /mnt/sandbox/CUSA02624_000/app0/intro/bo3_global_logo_logosequence.mkv
I have just to upload a new .mkv in 

    /data/CUSA02624/app0/intro/bo3_global_logo_logosequence.mkv
Now if OrbisAFP is loaded, the .mkv was loaded from /data and not /mnt/sandbox/... !

All file added in `/data/CUSA02624/` is like file in `/mnt/sandbox/CUSA02624_000/`

- If the file exist in `/data/CUSA02624/` and in `/mnt/sandbox/CUSA02624_000/`, the file in data is used
- If the file doesn't exist in `/data/CUSA02624/`, OrbisAFR use original file from `/mnt/sandbox/CUSA02624_000/`
- If the file exist in `/data/CUSA02624/` and not in `/mnt/sandbox/CUSA02624_000/`, the file in data is used

OrbisAFR doesn't just replace, but can also add new file in a game !

(Sorry for my bad english :P)
