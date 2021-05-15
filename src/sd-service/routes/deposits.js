const router   = require('express').Router(),
      dumpster = require('../models/Dumpster');

/* Gets all deposits */
router.get('/', function(req, res) {
    const data = groupDepositsByDate();
    const limit = req.query.limit !== undefined ? req.query.limit : 10;
    res.json(limitRecords(data, limit));
});

/* Gets a specific deposit using his id */
router.get('/:depositId', function(req, res) {
    const deposit = dumpster.getDeposits()[req.params.depositId];
    if(deposit === undefined) {
        res.statusMessage = "No item found with the specified index!";
        res.status(400).end();
    } else {
      res.json(deposit);
    }
});

/* Adds new deposit */
router.post('/', function(req, res) {
    const quantity = Number(req.body.quantity);
    if(dumpster.getStatus().available && quantity !== undefined && quantity) {
        dumpster.saveDeposit(createDeposit(quantity));
        res.json(dumpster.getDeposits());
    } else {
        res.statusMessage = "Request is not valid!";
        res.status(400).json(req.body);
    }
});


const groupDepositsByDate = () => (
    Object.values(dumpster.getDeposits().reduce((rv, x) => {
      rv[x['date']] = rv[x['date']] || { date: x['date'], deposits: [] }
      rv[x['date']].deposits.push(x.quantity);
      return rv;
    }, {}))
)

const createDeposit = (quantity) => {
    const currentDate = new Date().toISOString().slice(0,10);
    return { date: currentDate, quantity };
}

const limitRecords = (records, limit) => (
    records.slice(Math.max(records.length - limit, 0))
);

module.exports = router;
