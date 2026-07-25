"""Pydantic models for application state and validated slider inputs."""

from __future__ import annotations

from pydantic import BaseModel, Field, field_validator, model_validator

from bayes_app.math_core import BayesResult, compute_bayes


class ProbabilityInputs(BaseModel):
    """Validated slider inputs for Bayes' theorem.

    Attributes:
        prior: P(H) in [0, 1].
        likelihood: P(E|H) in [0, 1].
        false_positive: P(E|¬H) in [0, 1].
    """

    prior: float = Field(..., ge=0.0, le=1.0, description="P(H)")
    likelihood: float = Field(..., ge=0.0, le=1.0, description="P(E|H)")
    false_positive: float = Field(..., ge=0.0, le=1.0, description="P(E|¬H)")

    @field_validator("prior", "likelihood", "false_positive", mode="before")
    @classmethod
    def _coerce_finite(cls, value: object) -> float:
        if isinstance(value, bool) or not isinstance(value, (int, float)):
            raise ValueError("probability must be a real number")
        value_f = float(value)
        if value_f != value_f or value_f in (float("inf"), float("-inf")):
            raise ValueError("probability must be finite")
        return value_f

    def to_result(self) -> BayesResult:
        """Compute the Bayes result for these inputs."""
        return compute_bayes(self.prior, self.likelihood, self.false_positive)


class CustomLabels(BaseModel):
    """User-supplied labels for Custom mode.

    Attributes:
        hypothesis: Display name for H.
        evidence: Display name for E.
        question: Free-text framing of the inference question.
    """

    hypothesis: str = Field(default="Hypothesis H", max_length=120)
    evidence: str = Field(default="Evidence E", max_length=120)
    question: str = Field(
        default="What is P(H|E) given my prior and likelihoods?",
        max_length=400,
    )

    @field_validator("hypothesis", "evidence", "question")
    @classmethod
    def _strip(cls, value: str) -> str:
        cleaned = value.strip()
        return cleaned if cleaned else "—"


class AppState(BaseModel):
    """Full UI state snapshot for a single render pass.

    Attributes:
        mode_id: Active mode key (``medical``, ``trading``, ``custom``).
        inputs: Validated probability sliders.
        labels: Optional custom labels (Custom mode).
        population: Natural-frequency grid size.
    """

    mode_id: str = "medical"
    inputs: ProbabilityInputs
    labels: CustomLabels = Field(default_factory=CustomLabels)
    population: int = Field(default=1000, ge=10, le=10_000)

    @model_validator(mode="after")
    def _known_mode(self) -> AppState:
        allowed = {"medical", "trading", "custom"}
        if self.mode_id not in allowed:
            raise ValueError(f"mode_id must be one of {sorted(allowed)}")
        return self

    @property
    def result(self) -> BayesResult:
        """Live Bayes computation for the current inputs."""
        return self.inputs.to_result()
