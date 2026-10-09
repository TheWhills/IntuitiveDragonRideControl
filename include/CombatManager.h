#pragma once


namespace IDRC {   
    class FlyingModeManager;

    class CombatManager {
    public:
        static CombatManager& GetSingleton() {
            static CombatManager instance;
            return instance;
        }
        CombatManager(const CombatManager&) = delete;
        CombatManager& operator=(const CombatManager&) = delete;

        void InitializeData(RE::TESShout* a_unrelentingForceShout,
                            RE::TESShout* a_attackShout);
 
        bool DragonAttack(bool a_alternateAttack = false);

        void Update();
    
        bool IsShoutActive() {return m_shoutActive;}

        float GetShoutDirection() { return m_shoutDirection; }

        RE::Actor* GetShoutTarget() { return m_shoutTarget ? m_shoutTarget.get().get() : nullptr; }

        RE::Actor* GetStoredCombatTarget() { return m_storedCombatTarget ? m_storedCombatTarget.get().get() : nullptr; }

        RE::ActorHandle GetStoredCombatTargetHandle() { return m_storedCombatTarget; }

        int GetStoredCombatTargetState() { return m_storedCombatTargetState; }

        bool IsFastTravelAttack() { return m_isFastTravelAttack; }

        void SetFastTravelAttack(bool a_value) { m_isFastTravelAttack = a_value; }

        // [freeform-breath] true while a commanded attack is running in freeform mode (no actor target)
        bool IsFreeformShoutActive() const { return m_shoutActive && m_isFreeformShout; }

        // [freeform-breath] world-space point the camera is aiming at, kFreeformAimDistance ahead of the camera
        RE::NiPoint3 GetFreeformAimPoint() const;

    private:
        CombatManager() = default;
        ~CombatManager() = default;

        // accessed by other classes
        // change value only via Set function to trigger PropertyUpdateEvent
        RE::TESShout* m_unrelentingForceShout = nullptr;
        RE::TESShout* m_attackShout = nullptr;
        const float m_maxTargetDistance = 2000.0f;
        float m_shoutTimer = 0.0f;
        float m_shoutDirection = 1.0f;
        bool m_shoutActive = false;
        bool m_restartCombatPending = false;
        bool m_isFastTravelAttack = false;
        RE::ActorHandle m_shoutTarget{};
        RE::ActorHandle m_storedCombatTarget{};
        int m_storedCombatTargetState = 0;

        // [freeform-breath]
        // Distance from the camera to the synthetic aim point. Far enough that the parallax between
        // the camera and the dragon's head is small, close enough to stay inside the loaded area.
        static constexpr float kFreeformAimDistance = 4000.0f;
        // false = only the head/neck tracks the aim point; true = also feed it to the pathing look-at,
        // which can make the dragon's body turn toward it (may fight IDRC's flight steering).
        static constexpr bool kFreeformTurnBody = false;
        bool m_isFreeformShout = false;
        RE::ObjectRefHandle m_freeformMarker{};

        RE::TESObjectREFR* GetOrCreateFreeformMarker();
        void UpdateFreeformMarker();
        void ReleaseFreeformMarker();

        RE::TESShout* GetShout(float a_targetDistance);

        bool SetActiveShout(float a_targetDistance,  bool a_useUnrelentingForce = false);

        bool IsValidTarget(RE::Actor* a_target);

        void DragonStartCombat(RE::Actor* a_target);

        void UpdateCombat();

//        void UpdatePlayerCell();

        void UpdateAttack();

        void ExecuteAttack();

        float GetMaxTargetDistance();
    }; // class CombatManager
} // namespace IDRC

