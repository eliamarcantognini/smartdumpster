const router      = require('express').Router(),
      dumpster    = require('../models/Dumpster');

/* Get dumpster's status */
router.get('/', function(req, res) {
    res.json(dumpster.getStatus());
});


/* Updates dumpster's status */
router.put('/', function(req, res) {
    const available = req.body.available;
    const quantity = Number(req.body.quantity); 

    if(!checkUpdatedParams(available, quantity)) {
        res.statusMessage = "Params are not valid!";
        res.status(400).json(req.body);
    } else if(checkQuantity(available, quantity)) {
        res.statusMessage = "Dumpster has full!";
        res.status(400).json(req.body);
    } else {
        dumpster.setStatus(available, quantity) 
        res.json(dumpster.getStatus());
    }
});

const checkUpdatedParams = (available, quantity) => (
    available !== undefined && (typeof available === "boolean") && 
    quantity !== undefined && quantity
);

const checkQuantity = (available, quantity) => ( 
    available && dumpster.isFull() && quantity > dumpster.getCapacity() 
)

module.exports = router;
