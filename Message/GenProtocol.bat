set /p name=�����ļ�����Ȼ��س�
protoc.exe  --cpp_out=../Server/Server_rc2/proto  ./%name%.proto
copy *.proto ProtoGen /Y
cd ProtoGen
protogen -i:%name%.proto -o:%name%.cs -ns:proto.message
move /Y %name%.cs ..\..\Lib\ProtobufLib
pause