const express    = require('express'),
      bodyParser = require('body-parser'),
      cors       = require('cors');
      app        = express(),
      port       = process.env.PORT || 3000,
      status     = require('./routes/status'),
      token      = require('./routes/token');
      deposits   = require('./routes/deposits');

app.use(bodyParser.json()); // support json encoded bodies
app.use(bodyParser.urlencoded({ extended: true })); // support encoded bodies

app.use(cors());

app.use('/api/v1/status', status);
app.use('/api/v1/token', token);
app.use('/api/v1/deposits', deposits);

app.listen(port, () => console.log('Dumpster service listening on port: ' + port));
