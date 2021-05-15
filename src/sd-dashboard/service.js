const express    = require('express'),
      path       = require( "path" ),
      app        = express(),
      port       = process.env.PORT || 8080,
      publicDir  = path.resolve( __dirname, "public" );

app.use(express.static(publicDir) );

app.get("*", function(req, res) {
    res.sendFile(path.resolve(publicDir, "index.html"));
});

app.listen(port, () => console.log('Dumpster dashboard listening on port: ' + port));

