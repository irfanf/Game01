@echo off

echo app.keystore�t�@�C���𐶐����܂�

if exist app.keystore rm app.keystore

"%JAVA_HOME%\bin\keytool" -v -genkey -keystore .\app.keystore -validity 10000 -dname "cn=Irfan Fahmi, ou=GameScience, o=TridentComputer, c=JP" -keypass irfan135 -storepass zoldic123

echo �����I

pause