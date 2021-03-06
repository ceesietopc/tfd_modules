(define (problem CrewPlanning_2crew_1day_60utilization)
  (:domain CrewPlanningOpl)
  (:objects
    d0 - Day
    d1 - Day
    d2 - Day
    c1 - CrewMember
    c2 - CrewMember
    ms1 - MedicalState
    ms2 - MedicalState
    spaceshipFilter - FilterState
    rpcm1 - RPCM
    e1 - ExerEquipment
    pa1_1 - PayloadAct
    pa1_2 - PayloadAct
    pa1_3 - PayloadAct
    pa1_4 - PayloadAct
    pa1_5 - PayloadAct
    pa1_6 - PayloadAct
    pa1_7 - PayloadAct
    pa1_8 - PayloadAct
    pa1_9 - PayloadAct
  )
  (:init
    (Day_next d0 d1)
    (Day_next d1 d2)
    (Day_initiated d1)
    (CrewMember_currentDay c1 d0)
    (CrewMember_doneSleep c1 d0)
    (CrewMember_available c1)
    (CrewMember_currentDay c2 d0)
    (CrewMember_doneSleep c2 d0)
    (CrewMember_available c2)
    (ExerEquipment_unused e1)
  )
  (:goal (and
      (CrewMember_doneSleep c1 d1)
      (CrewMember_doneSleep c2 d1)
      (MedicalState_finished ms2 d1)
      (Day_initiated d2)
      (PayloadAct_completed pa1_1 d1)
      (PayloadAct_completed pa1_2 d1)
      (PayloadAct_completed pa1_3 d1)
      (PayloadAct_completed pa1_4 d1)
      (PayloadAct_completed pa1_5 d1)
      (PayloadAct_completed pa1_7 d1)
      (PayloadAct_completed pa1_8 d1)
      (PayloadAct_completed pa1_9 d1)
      (PayloadAct_completed pa1_6 d1)))
)
