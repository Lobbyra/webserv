echo "Don't launch the script by ./ but by eval $\(cat ./env_for_cgi/\)";

export REQUEST_METHOD=POST;
export SERVER_PROTOCOL=HTTP/1.1;
export PATH_INFO=/directory/youpi.bla;
