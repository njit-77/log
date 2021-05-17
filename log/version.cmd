@echo on

set revfile="%~dp0version.h"

for /f "delims=+ " %%a in ('git rev-list HEAD --count') do @set revnum=%%a
for /f "delims=+ " %%a in ('git rev-parse --short HEAD') do @set revset=%%a
for /f "delims=+ " %%a in ('git rev-parse HEAD') do @set HEAD=%%a

echo //Auto generate file version > %revfile%

echo #define	LOG_Major_Version	%date:~0,4%	>> %revfile%
echo #define	LOG_Minor_Version	%date:~5,2%	>> %revfile%
echo #define	LOG_Revsion_Version	%date:~8,2%	>> %revfile%
echo #define	LOG_RevNum_Version	%revnum% >> %revfile%
echo #define	LOG_Git_Info	"%HEAD%" >> %revfile%
echo #define	LOG_Product_Version	"%date:~0,4%.%date:~5,2%.%date:~8,2%.%revnum%" >> %revfile%
echo #define	LOG_File_Description	"%revset%  %date:~0,4%.%date:~5,2%.%date:~8,2% / %time%" >> %revfile%
