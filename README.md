# Project Bullet Hell

Bullet hell action game inspired by Returnal and Kill Knight. Player-focused
vertical slice, built in Unreal Engine 5.8, C++, with GAS (Gameplay Ability
System) driving abilities/attributes and GASP (Epic's Game Animation Sample
Project) as the animation/locomotion reference layer.

## First-time setup

1. Install Unreal Engine **5.8** via the Epic Games Launcher (or build from
   source if you're on that workflow).
2. Right-click `ProjectBulletHell.uproject` → **Generate Visual Studio project
   files** (Windows) or equivalent for your platform/IDE.
3. Open the generated `.sln` / workspace and build the `Development Editor`
   configuration, or just double-click the `.uproject` to let the editor
   prompt a build.
4. On first open, the editor will complain about missing content until the
   greybox level and starting assets exist - that's expected at this stage.

## Git LFS

This repo tracks binary asset types (`.uasset`, `.umap`, textures, audio,
fbx) via Git LFS - see `.gitattributes`. Run `git lfs install` once per
machine before your first `git add` of real content. Set this up **before**
committing any real assets; migrating LFS in after the fact is painful.

## Folder structure

```
Source/ProjectBulletHell/
  Core/        - GameMode, GameState, GameInstance
  Player/      - PlayerCharacter, PlayerState, PlayerController
  Abilities/   - GAS: AttributeSet, ASC subclass, base GameplayAbility,
                 native gameplay tags
  Weapons/     - weapon base classes (empty for now - next milestone)
  Movement/    - movement component extensions, if CMC subclassing is
                 needed beyond what GAS-driven abilities cover
  UI/          - HUD / player UI

Content/_Game/
  Player/      - player mesh, animation blueprint, IK rig (GASP-derived)
  Abilities/   - GameplayEffect / GameplayAbility Blueprint assets, data
                 assets for tunable dash/movement/weapon values
  Weapons/     - weapon meshes, projectile BPs, VFX/SFX hookups
  VFX/, Audio/, UI/
  Levels/Greybox/ - gray-box test arena(s) for movement/gunplay iteration
```

`_Game` is prefixed with an underscore so it sorts above any imported
plugin/marketplace content folders in the Content Browser.

## Architecture notes (see also: design discussion this scaffold came from)

- **ASC + AttributeSet live on `APBHPlayerState`**, not the Character - the
  Character forwards `IAbilitySystemInterface` to it. Standard GAS pattern;
  matters if pawns are ever re-possessed (checkpoint respawns, biome resets).
- **Abilities are the source of truth for gameplay verbs** (dash, fire, alt-fire).
  The Character class only owns input binding and forwards activation by
  gameplay tag (`PBHGameplayTags::Ability_Dash`, etc.) - it does not contain
  dash/fire logic itself. Keep it that way; movement/gunplay tuning should
  live in ability + data asset land, not hardcoded in the pawn.
- **CharacterMovementComponent (not Mover)** is the movement base for now.
  Mover is still experimental as of 5.7/5.8 - revisit only if rollback
  networking becomes a hard requirement.
- **GASP is a reference/asset source, not a base class.** Pull in its
  skeleton, IK rig, and animation blueprint patterns; do not inherit its
  sample Character/Pawn Blueprints.

## Next milestones

1. Import/adapt GASP skeleton + anim blueprint onto `APBHPlayerCharacter`.
2. Build `Ability.Dash` (GameplayAbility + GameplayEffect for i-frames via
   `State.Invulnerable` tag + cooldown) and prototype it in the greybox level.
3. Build `Ability.Fire.Primary` (hitscan or projectile - TBD) with input
   buffering.
4. Block out `L_Greybox_Test` with a bullet-spawner test actor for dodge
   timing iteration.
