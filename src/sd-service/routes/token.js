const router = require('express').Router();

const dumpster = require('../models/Dumpster');

/* Gets token */
router.get('/', function(req, res) {
    res.json(dumpster.getStatus().available ? generateToken() : "");
});

const generateToken = function() {
    return Math.random().toString(36).substr(2);
}

module.exports = router;
