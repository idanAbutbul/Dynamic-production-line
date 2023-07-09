const express = require('express');
const router = express.Router();
module.exports = router;

const timeModel = require('../models/Time_M');

router.get('/Add', async (req, res) => {
    let time_data = await timeModel.find();
    res.render('timeAdd', {
        pageTitle: 'Times',
        item: {},
        data: time_data
    });
});

router.post('/Add', (req, res) => {
    const modelData = new timeModel({
        Heating: req.body.Heating,
        Light_Level: req.body.Light_Level,
        Activation: req.body.Activation,
        Pause: req.body.Pause
    });
    modelData.save();
    res.redirect('/Add');
});

router.get('/api/times', async (req, res) => {
    try {
      const timeData = await timeModel.find();
      res.json(timeData);
    } catch (error) {
      res.status(500).json({ error: 'An error occurred' });
    }
  });
  
  router.get('/Add', async (req, res) => {
    let time_data = await timeModel.find();
    res.json(time_data);
  });
