# JMON User Manual

## Quick Start Guide
1. Power on your system
2. Default display shows address and data sections
3. Initial editing location: 0800


## How to Enter Data
1. Simply type hex digits (0-F)
2. Data appears in right display
3. Location auto-increments after two digits
4. Use + or - to move between locations manually

## Basic Data Entry Mode
- Default mode when JMON starts
- Shows an address in left display and data in right display
- Current editing location is displayed on left
- Data at that location is displayed on right

## Step-by-Step Data Entry Process
1. **View Current Location**
   - Left display shows current memory address
   - Right display shows current byte value at that address
   - Dots indicate which mode you're in:
     - No dots = Data entry mode
     - Four dots = Address entry mode

2. **Enter First Nibble (0-F)**
   - Press any hex key (0-9 or A-F)
   - Value appears in left half of right display
   - Old value remains in right half
   - Monitor Control Byte tracks this as one nibble entered

3. **Enter Second Nibble (0-F)**
   - Press second hex key (0-9 or A-F)
   - Value appears in right half of display
   - Complete byte is now entered
   - Data is written to memory at current location

4. **Auto-Increment**
   - After second nibble entry:
     - Location automatically advances to next address
     - New address shows in left display
     - Ready for next byte entry
   - Can be disabled by setting memory location 0827

## Manual Navigation
- Use `+` key to:
   - Move to next memory location
   - Increment current address by 1

- Use `-` key to:
   - Move to previous memory location
   - Decrement current address by 1

## Tips and Tricks
1. **Entering Multiple Bytes**
   - Let auto-increment handle address advancement
   - Just keep entering hex pairs
   - Monitor automatically moves to next location

2. **Correcting Mistakes**
   - Use + or - to return to incorrect location
   - Enter new hex values to overwrite
   - Both nibbles must be re-entered

3. **Checking Work**
   - Use + and - to review entered data
   - Data shows in right display as you move
   - No data is changed unless you enter new values

4. **Visual Feedback**
   - Monitor Control Byte (082B) tracks:
     - Number of nibbles entered
     - Current mode
     - Auto-increment status

## Common Errors to Avoid
1. **Partial Entry**
   - Always complete both nibbles
   - Half-entered bytes may not be stored correctly

2. **Wrong Mode**
   - Ensure no dots are showing for data entry
   - If dots appear, you're in address mode
   - Press AD to return to data mode

3. **Lost Position**
   - Note starting address before long sequences
   - Use address mode to return to known location

4. **Auto-Increment Issues**
   - If location isn't advancing automatically:
     - Check memory location 0827
     - Verify you're entering complete bytes
     - Ensure you're in data mode

## Special Considerations
- Each memory location holds one byte (00-FF)
- First nibble entered goes to high order position
- Second nibble goes to low order position
- Invalid hex keys are ignored
- Current location is preserved during mode changes







# How to Change Address
1. Press AD key
2. Notice four dots appear in display
3. Enter new address using hex digits
4. System returns to data mode automatically





# How to Save Programs to Tape
1. Enter SHIFT+0 (or AD+0)
2. Press + until "SAVE-H" appears
   - H = High speed (600 baud)
   - L = Low speed (300 baud)
3. Press GO
4. Enter file parameters:
   - File number (e.g., "00-F")
   - Start address ("-S")
   - End address ("-E")
   - Optional auto-GO address ("-G")
5. Start tape recording
6. Press GO to begin save
7. Wait for "-END-S" display
8. Remember: Always save important programs multiple times and verify loads before relying on tape storage.



# How to Test Tape Saves
1. Enter SHIFT+0 (or AD+0)
2. Select test option:
   - "TEST-BL" = Block test
   - "TEST-CS" = Checksum test
3. Enter file number
4. Start tape
5. Watch for results:
   - "PASS CS" = Good checksum
   - "PASS Tb" = Good block test
   - "FAIL CS" = Bad checksum
   - "FAIL Tb" = Bad block test



# How to Load Programs
1. Enter SHIFT+0 (or AD+0)
2. Press + until "LOAD-T" appears
3. Press GO
4. Enter parameters:
   - File number (or FFFF for next file)
   - Start address (optional override)
5. Start tape playback
6. Press GO
7. Watch for completion message:
   - "PASS Ld" = Success
   - "FAIL Ld" = Error




# How to Single Step Through Code
1. Position to start address
2. Enter stepping mode
3. Display shows register contents:
   - Press + to view next register
   - Press - to view previous register
4. Available registers:
   - PC = Program Counter
   - AF = Accumulator/Flags
   - BC, DE, HL = Register pairs
   - IX, IY = Index registers
   - SP = Stack Pointer
5. Use GO to execute next instruction



# How to Use Auto-Increment
1. Feature is active by default
2. After entering two digits:
   - Location automatically advances
   - Ready for next data entry
3. To disable:
   - See memory location 0827
   - Set to non-zero value


# How to Perform Reset
Soft Reset:
1. Normal reset operation
2. Preserves user patches
3. Maintains current settings

Hard Reset:
1. Hold any key while resetting
2. Clears all user patches
3. Resets all variables to default

# Error Recovery
When you see:
1. "Err-In":
   - Check input parameters
   - Verify address range
2. "FAIL" messages:
   - Check tape speed setting
   - Clean tape head
   - Adjust volume level
   - Try alternative load address

# Advanced Operations

## How to Use LCD (If Fitted)
1. System auto-detects LCD
2. Displays show:
   - Current mode
   - ASCII data
   - Status information

## How to Use Menu System
1. Enter via SHIFT+0 or AD+0
2. Navigate:
   - + key moves forward
   - - key moves backward
3. Select with GO
4. Exit with AD key

## How to Set Auto-Execute
1. During save operation
2. At "-G" prompt:
   - Enter execution address
   - Or FFFF for no auto-execute
3. Program will auto-run on successful load

# Memory Map Reference
Important Locations:
- 082E: Current Edit Location
- 082B: Monitor Control Byte
- 082A: Auto Key Status
- 0825: Key Press Flag
- 0820: Key Input Buffer

# Maintenance Tips
1. Clean tape heads regularly
2. Verify power supply stability
3. Check keyboard connections
4. Maintain consistent tape speed
5. Store programs with clear labels

Need help? Look for:
- Display indicators
- Audible feedback
- Error messages
- Status displays

 
